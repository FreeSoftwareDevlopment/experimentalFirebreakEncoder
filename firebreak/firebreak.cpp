#include "pch.h"
#include "framework.h"
#include "firebreak.h"
#include <memory>

struct bitpos {
	size_t pos = 0;
	BIT bit = 0;
};

size_t cEXS(BIT b) {
	const size_t multip = 8 * sizeof(char);
	size_t rep = b % multip;
	return ((b - rep) / multip) + (rep > 0 ? 1 : 0);
}

void writeBit(char* b, BIT pos, bool high = true) {
	char bstr = (0x80 >> pos);
	if (high) *b |= bstr;
	else if (*b & bstr) *b ^= bstr;
}

#define readBit(b, pos) (b & (0x80 >> pos))

bool Cfirebreak::encoder(size_t bufsize, char* bw) {
#define bufr bw
	bitpos bp, bp2;
	firebreakstruct* fb;
	for (size_t currentV = 0, celem = 0; currentV < br1.size(); currentV++) {
		fb = &(br1[currentV]);
		celem = cEXS(fb->bit);
		if (fb->data != nullptr) {
			char* p = (char*)fb->data;
			for (bp2.pos = 0; bp2.pos < celem; bp2.pos++) {
				char w = p[bp2.pos];
				if (bp.pos >= bufsize) return 0;
				for (bp2.bit = 0; bp2.bit < ((bp2.pos < celem - 1) ? 8 : (fb->bit % 8 > 0 ? fb->bit % 8 : 8)); bp2.bit++) {
					writeBit(&bufr[bp.pos], bp.bit, readBit(w, 7 - bp2.bit));// REVERSE BITS (BECAUSE BOOL IS ONLY 1 BIT AND IS AS CHAR (true) 0b00000001)
					bp.bit++;
					if (bp.bit >= 8) { bp.bit = 0; bp.pos++; }
				}
			}
		}
	}
#undef bufr
	return 1;
}

char* Cfirebreak::makeBuffer(size_t* buffersize)
{
	size_t exactSize = cEXS(bitcounter),
		bufsize = sizeof(char) * exactSize;
	if (buffersize != nullptr) {
		(*buffersize) = bufsize;
	}

	freeBuffer();

	bufr = (char*)malloc(bufsize);
	if (bufr == nullptr) {
		return nullptr;
	}
	memset(bufr, 0x00, bufsize);

	return encoder(bufsize, bufr) ? bufr : nullptr;
}

void Cfirebreak::freeBuffer()
{
	if (bufr == nullptr)
		return;
	free(bufr);
	bufr = nullptr;
}

Cfirebreak::~Cfirebreak()
{
	freeBuffer();
}
