#ifdef FIREBREAK_EXPORTS
#define FIREBREAK_API __declspec(dllexport)
#else
#define FIREBREAK_API __declspec(dllimport)
#endif
#include <vector>

typedef unsigned int firebreakLoc;
typedef firebreakLoc BIT;
struct FIREBREAK_API firebreakstruct {
	BIT bit = 0;
	void* data;
	firebreakstruct(BIT bits, void* datar = nullptr);
	firebreakstruct();
};
typedef std::vector<firebreakstruct> firebreaks;

class FIREBREAK_API Cfirebreak {
private:
	firebreaks br1;
	BIT bitcounter = 0;
	char* bufr = nullptr;
	bool encoder(size_t bufsize, char* bw);
public:
	Cfirebreak(void);
	firebreakLoc AddBool(bool* b);
	firebreakLoc AddData(void* b, BIT bits);
	firebreakLoc AddInt(int* b);
	firebreakLoc AddDataSiz(void* b, size_t size);
	char* makeBuffer(size_t* buffersize = nullptr);
	void freeBuffer();
	~Cfirebreak();
};
