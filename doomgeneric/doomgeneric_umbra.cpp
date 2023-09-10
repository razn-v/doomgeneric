#include "doomkeys.h"

#include "doomgeneric.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <gui/gui.hpp>

static int key = 0;

static unsigned char convertToDoomKey(Keyboard::KeyCode code, char ascii)
{
	unsigned char converted;
	switch (code)
	{
	case Keyboard::KeyCode::Enter:
		return KEY_ENTER;
	case Keyboard::KeyCode::Escape:
		return KEY_ESCAPE;
	case Keyboard::KeyCode::LeftControl:
		return KEY_FIRE;
	case Keyboard::KeyCode::Space:
		return KEY_USE;
	case Keyboard::KeyCode::LeftShift:
	case Keyboard::KeyCode::RightShift:
		return KEY_RSHIFT;
	case Keyboard::KeyCode::UpArrow:
		return KEY_UPARROW;
	case Keyboard::KeyCode::DownArrow:
		return KEY_DOWNARROW;
	case Keyboard::KeyCode::LeftArrow:
		return KEY_LEFTARROW;
	case Keyboard::KeyCode::RightArrow:
		return KEY_RIGHTARROW;
	default:
		return ascii;
	}

	return converted;
}

void DG_Init()
{
	return;
}


void DG_DrawFrame()
{
	Keyboard::KeyboardEvent event;

	if (get_kb_event(&event)) {
		key = convertToDoomKey(event.key_code, event.ascii);
		key |= event.pressed << 16;
	}

	draw_from_buffer(DG_ScreenBuffer, DOOMGENERIC_RESX, DOOMGENERIC_RESY);
}

void DG_SleepMs(uint32_t ms)
{
    usleep(ms * 1000);
}

uint32_t DG_GetTicksMs()
{
    struct timeval  tp;
    struct timezone tzp;

    gettimeofday(&tp, &tzp);

    return (tp.tv_sec * 1000) + (tp.tv_usec / 1000); /* return milliseconds */
}

int DG_GetKey(int* pressed, unsigned char* doomKey)
{
	if (key != 0)
	{
		*pressed = key >> 8;
		*doomKey = key & 0xFF;
		key = 0;

		return 1;
	}

	return 0;
}

void DG_SetWindowTitle(const char * title)
{
    return;
}

int main(int argc, char **argv)
{
    doomgeneric_Create(argc, argv);

    for (int i = 0; ; i++)
    {
        doomgeneric_Tick();
    }

    return 0;
}
