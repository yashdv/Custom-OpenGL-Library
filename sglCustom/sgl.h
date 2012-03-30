#define SGL_TRIANGLES 1

void fillidentity(float *);
void initialize();
void multiply(float *, float *,float *);

void sglMPushMatrix();
void sglMPopMatrix();
void sglMTranslate(float *);
void sglMScale(float *);
void sglMMatrix(float *);
void sglMLoadIdentity();
void sglMRotate(float, float *);

void sglVRotate(float,float *);
void sglVTranslate(float *);
void sglLookAt(float *, float *, float *);
void sglVMatrix(float *);
void sglVLoadIdentity();

void sglProjOrtho(float,float,float,float,float,float);
void sglProjFrustum(float,float,float,float,float,float);

void sglViewport(float,float,float,float);

void sglBegin(int);
void sglEnd();
void sglColour(float,float,float);
void sglClear(float,float,float);
void sglVertex(float *);
void sglShow();
