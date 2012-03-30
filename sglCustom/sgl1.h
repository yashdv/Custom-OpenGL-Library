void fillidentity(float *);
void initialize();
void multiply(float *, float *,float *);

void sglMPushMatrix();
void sglMPopMatrix();
void sglMTranslate(float,float,float);
void sglMScale(float,float,float);
void sglMMatrix(float *);
void sglMLoadIdentity();
void sglMRotate(float,float,float,float);

void sglVRotate(float,float,float,float);
void sglVTranslate(float,float,float);
void sglLookAt(float,float,float, float,float,float, float,float,float);
void sglVMatrix(float *);
void sglVLoadIdentity();

void sglProjOrtho(float,float,float,float,float,float);
void sglProjFrustum(float,float,float,float,float,float);

void sglViewport(float,float,float,float);

void sglBegin(int);
void sglEnd();
void sglColour(float,float,float);
void sglClear(float,float,float);
void sglVertex(float,float,float);
void sglShow();
