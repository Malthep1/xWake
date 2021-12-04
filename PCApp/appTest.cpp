#include "CommandCtrl.h"
#include <time.h>

#include "Serial.h"
using std::time_t; 

int main(void)
{
	CommandCtrl commandCtrl;

	while (commandCtrl.running)
	{
		commandCtrl.getNextCommand();
	}
}