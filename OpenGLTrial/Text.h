#include <GL\glew.h>
#include <GL\freeglut.h>

class Text
{
private:
	char * string;
	void * font;
public:
	Text(char * string, void * font);

	void displayText();
};

