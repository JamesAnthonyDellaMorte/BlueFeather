#include "common.h"

#include <math.h>

extern float cosf(float);
extern float sinf(float);
extern float sqrtf(float);

void guMtxF2L(float mf[4][4], Mtx* m) {
    int i;
    int j;
    int e1;
    int e2;
    int* ai = (int*)&m->m[0][0];
    int* af = (int*)&m->m[2][0];

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 2; j++) {
            e1 = FTOFIX32(mf[i][j * 2]);
            e2 = FTOFIX32(mf[i][j * 2 + 1]);
            *(ai++) = (e1 & 0xffff0000) | ((e2 >> 16) & 0xffff);
            *(af++) = ((e1 << 16) & 0xffff0000) | (e2 & 0xffff);
        }
    }
}

void guMtxL2F(float mf[4][4], Mtx* m) {
    int i;
    int j;
    unsigned int e1;
    unsigned int e2;
    unsigned int* ai = (unsigned int*)&m->m[0][0];
    unsigned int* af = (unsigned int*)&m->m[2][0];
    int q1;
    int q2;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 2; j++) {
            e1 = (*ai & 0xffff0000) | ((*af >> 16) & 0xffff);
            e2 = ((*(ai++) << 16) & 0xffff0000) | (*(af++) & 0xffff);
            q1 = *((int*)&e1);
            q2 = *((int*)&e2);

            mf[i][j * 2] = FIX32TOF(q1);
            mf[i][j * 2 + 1] = FIX32TOF(q2);
        }
    }
}

void guMtxIdentF(float mf[4][4]) {
    int i;
    int j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            mf[i][j] = (i == j) ? 1.0f : 0.0f;
        }
    }
}

void guMtxIdent(Mtx* m) {
    float mf[4][4];

    guMtxIdentF(mf);
    guMtxF2L(mf, m);
}

void guTranslateF(float mf[4][4], float x, float y, float z) {
    guMtxIdentF(mf);
    mf[3][0] = x;
    mf[3][1] = y;
    mf[3][2] = z;
}

void guTranslate(Mtx* m, float x, float y, float z) {
    float mf[4][4];

    guTranslateF(mf, x, y, z);
    guMtxF2L(mf, m);
}

void guScaleF(float mf[4][4], float x, float y, float z) {
    guMtxIdentF(mf);
    mf[0][0] = x;
    mf[1][1] = y;
    mf[2][2] = z;
    mf[3][3] = 1.0f;
}

void guScale(Mtx* m, float x, float y, float z) {
    float mf[4][4];

    guScaleF(mf, x, y, z);
    guMtxF2L(mf, m);
}

void guOrthoF(float mf[4][4], float l, float r, float b, float t, float n, float f, float scale) {
    int i;
    int j;

    guMtxIdentF(mf);

    mf[0][0] = 2.0f / (r - l);
    mf[1][1] = 2.0f / (t - b);
    mf[2][2] = -2.0f / (f - n);
    mf[3][0] = -(r + l) / (r - l);
    mf[3][1] = -(t + b) / (t - b);
    mf[3][2] = -(f + n) / (f - n);
    mf[3][3] = 1.0f;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            mf[i][j] *= scale;
        }
    }
}

void guOrtho(Mtx* m, float l, float r, float b, float t, float n, float f, float scale) {
    float mf[4][4];

    guOrthoF(mf, l, r, b, t, n, f, scale);
    guMtxF2L(mf, m);
}

void guPerspectiveF(float mf[4][4], u16* perspNorm, float fovy, float aspect, float near, float far, float scale) {
    float cot;
    int i;
    int j;

    guMtxIdentF(mf);

    fovy *= 3.1415926f / 180.0f;
    cot = cosf(fovy / 2.0f) / sinf(fovy / 2.0f);

    mf[0][0] = cot / aspect;
    mf[1][1] = cot;
    mf[2][2] = (near + far) / (near - far);
    mf[2][3] = -1.0f;
    mf[3][2] = (2.0f * near * far) / (near - far);
    mf[3][3] = 0.0f;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            mf[i][j] *= scale;
        }
    }

    if (perspNorm != NULL) {
        if (near + far <= 2.0f) {
            *perspNorm = (u16)0xFFFF;
        } else {
            *perspNorm = (u16)((2.0f * 65536.0f) / (near + far));
            if (*perspNorm <= 0) {
                *perspNorm = (u16)0x0001;
            }
        }
    }
}

void guPerspective(Mtx* m, u16* perspNorm, float fovy, float aspect, float near, float far, float scale) {
    float mf[4][4];

    guPerspectiveF(mf, perspNorm, fovy, aspect, near, far, scale);
    guMtxF2L(mf, m);
}

void guLookAtF(float mf[4][4], float xEye, float yEye, float zEye, float xAt, float yAt, float zAt, float xUp,
               float yUp, float zUp) {
    float len;
    float xLook;
    float yLook;
    float zLook;
    float xRight;
    float yRight;
    float zRight;

    guMtxIdentF(mf);

    xLook = xAt - xEye;
    yLook = yAt - yEye;
    zLook = zAt - zEye;

    len = -1.0f / sqrtf((xLook * xLook) + (yLook * yLook) + (zLook * zLook));
    xLook *= len;
    yLook *= len;
    zLook *= len;

    xRight = (yUp * zLook) - (zUp * yLook);
    yRight = (zUp * xLook) - (xUp * zLook);
    zRight = (xUp * yLook) - (yUp * xLook);
    len = 1.0f / sqrtf((xRight * xRight) + (yRight * yRight) + (zRight * zRight));
    xRight *= len;
    yRight *= len;
    zRight *= len;

    xUp = (yLook * zRight) - (zLook * yRight);
    yUp = (zLook * xRight) - (xLook * zRight);
    zUp = (xLook * yRight) - (yLook * xRight);
    len = 1.0f / sqrtf((xUp * xUp) + (yUp * yUp) + (zUp * zUp));
    xUp *= len;
    yUp *= len;
    zUp *= len;

    mf[0][0] = xRight;
    mf[1][0] = yRight;
    mf[2][0] = zRight;
    mf[3][0] = -((xEye * xRight) + (yEye * yRight) + (zEye * zRight));

    mf[0][1] = xUp;
    mf[1][1] = yUp;
    mf[2][1] = zUp;
    mf[3][1] = -((xEye * xUp) + (yEye * yUp) + (zEye * zUp));

    mf[0][2] = xLook;
    mf[1][2] = yLook;
    mf[2][2] = zLook;
    mf[3][2] = -((xEye * xLook) + (yEye * yLook) + (zEye * zLook));

    mf[0][3] = 0.0f;
    mf[1][3] = 0.0f;
    mf[2][3] = 0.0f;
    mf[3][3] = 1.0f;
}

void guLookAt(Mtx* m, float xEye, float yEye, float zEye, float xAt, float yAt, float zAt, float xUp, float yUp,
              float zUp) {
    float mf[4][4];

    guLookAtF(mf, xEye, yEye, zEye, xAt, yAt, zAt, xUp, yUp, zUp);
    guMtxF2L(mf, m);
}

void guRotateRPYF(float mf[4][4], float r, float p, float h) {
    const float dtor = 3.1415926f / 180.0f;
    float sinr;
    float sinp;
    float sinh;
    float cosr;
    float cosp;
    float cosh;

    r *= dtor;
    p *= dtor;
    h *= dtor;
    sinr = sinf(r);
    cosr = cosf(r);
    sinp = sinf(p);
    cosp = cosf(p);
    sinh = sinf(h);
    cosh = cosf(h);

    guMtxIdentF(mf);

    mf[0][0] = cosp * cosh;
    mf[0][1] = cosp * sinh;
    mf[0][2] = -sinp;

    mf[1][0] = (sinr * sinp * cosh) - (cosr * sinh);
    mf[1][1] = (sinr * sinp * sinh) + (cosr * cosh);
    mf[1][2] = sinr * cosp;

    mf[2][0] = (cosr * sinp * cosh) + (sinr * sinh);
    mf[2][1] = (cosr * sinp * sinh) - (sinr * cosh);
    mf[2][2] = cosr * cosp;
}

void guRotateRPY(Mtx* m, float r, float p, float h) {
    float mf[4][4];

    guRotateRPYF(mf, r, p, h);
    guMtxF2L(mf, m);
}

void guNormalize(float* x, float* y, float* z) {
    float length = 1.0f / sqrtf((*x * *x) + (*y * *y) + (*z * *z));
    *x *= length;
    *y *= length;
    *z *= length;
}
