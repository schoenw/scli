#ifndef MD5_H
#define MD5_H

struct MD5Context {
	guint32 buf[4];
	guint32 bits[2];
	guchar  in[64];
	int     doByteReverse;
};

void MD5Init(struct MD5Context *context);
void MD5Update(struct MD5Context *context, guchar const *buf,
	       guint len);
void MD5Final(guchar digest[16], struct MD5Context *context);
void MD5Transform(guint32 buf[4], guint32 const in[16]);

/*
 * This is needed to make RSAREF happy on some MS-DOS compilers.
 */
typedef struct MD5Context MD5_CTX;

#endif /* !MD5_H */
