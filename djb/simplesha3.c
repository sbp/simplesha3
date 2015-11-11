/* Version 20150922. Public domain. */

#include "Python.h"

#define FOR(i,n) for (i = 0;i < n;++i)
#define H(i,r,p,d,name) \
  static PyObject *i(PyObject *self,PyObject *args) \
  { \
    u8 h[d]; \
    u8 *m; \
    int n; \
    if (!PyArg_ParseTuple(args,"s#:update",&m,&n)) return 0; \
    Keccak(r*8,m,n,p,h,d); \
    return PyString_FromStringAndSize((const char *)h,d); \
  } \
  PyDoc_STRVAR(i##_doc,"Return the "name" digest of the input string.");

/* core copied from https://twitter.com/tweetfips202 */
typedef unsigned char u8;typedef unsigned long long u64;static u64 ROL(u64 a,u8 n){return(a<<n)|(a>>(64-n));}static u64 L64(const u8*x){u64
r=0,i;FOR(i,8)r|=(u64)x[i]<<8*i;return r;}static void F(u64*s){u8 x,y,j,R=1,r,n;u64 t,B[5],Y;FOR(n,24){FOR(x,5){B[x]=0;FOR(y,5)B[x]^=s[x+5*y
];}FOR(x,5){t=B[(x+4)%5]^ROL(B[(x+1)%5],1);FOR(y,5)s[x+5*y]^=t;}t=s[1];y=r=0;x=1;FOR(j,24){r+=j+1;Y=2*x+3*y;x=y;y=Y%5;Y=s[x+5*y];s[x+5*y]=
ROL(t,r%64);t=Y;}FOR(y,5){FOR(x,5)B[x]=s[x+5*y];FOR(x,5)s[x+5*y]=B[x]^(~B[(x+1)%5]&B[(x+2)%5]);}FOR(y,7)if((R=(R<<1)^(113*(R>>7)))&2)*s^=
1ULL<<((1<<y)-1);}}static void Keccak(u8 r,const u8*m,u64 n,u8 p,u8*h,u64 d){u64 s[25],i;u8 t[200];FOR(i,25)s[i]=0;while(n>=r){FOR(i,r/8)s[i
]^=L64(m+8*i);F(s);n-=r;m+=r;}FOR(i,r)t[i]=0;FOR(i,n)t[i]=m[i];t[i]=p;t[r-1]|=128;FOR(i,r/8)s[i]^=L64(t+8*i);F(s);FOR(i,d)h[i]=s[i/8]>>8*(i%
8);}

H(shake128,21,31,168,"single-block SHAKE128")
H(shake256,17,31,136,"single-block SHAKE256")
H(sha3224,18,6,28,"SHA3-224")
H(sha3256,17,6,32,"SHA3-256")
H(sha3384,13,6,48,"SHA3-384")
H(sha3512,9,6,64,"SHA3-512")
H(keccakc448,18,1,28,"Keccak-224")
H(keccakc512,17,1,32,"Keccak-256")
H(keccakc768,13,1,48,"Keccak-384")
H(keccakc1024,9,1,64,"Keccak-512")

static struct PyMethodDef functions[] = {
  {"sha3224",(PyCFunction)sha3224,METH_VARARGS|METH_KEYWORDS,sha3224_doc},
  {"sha3256",(PyCFunction)sha3256,METH_VARARGS|METH_KEYWORDS,sha3256_doc},
  {"sha3384",(PyCFunction)sha3384,METH_VARARGS|METH_KEYWORDS,sha3384_doc},
  {"sha3512",(PyCFunction)sha3512,METH_VARARGS|METH_KEYWORDS,sha3512_doc},
  {"shake128",(PyCFunction)shake128,METH_VARARGS|METH_KEYWORDS,shake128_doc},
  {"shake256",(PyCFunction)shake256,METH_VARARGS|METH_KEYWORDS,shake256_doc},
  {"keccakc448",(PyCFunction)keccakc448,METH_VARARGS|METH_KEYWORDS,keccakc448_doc},
  {"keccakc512",(PyCFunction)keccakc512,METH_VARARGS|METH_KEYWORDS,keccakc512_doc},
  {"keccakc768",(PyCFunction)keccakc768,METH_VARARGS|METH_KEYWORDS,keccakc768_doc},
  {"keccakc1024",(PyCFunction)keccakc1024,METH_VARARGS|METH_KEYWORDS,keccakc1024_doc},
  {0,0}
};

PyMODINIT_FUNC initsimplesha3(void)
{
  Py_InitModule("simplesha3",functions);
}
