#include "Application.h"

int main()
{
	Application app;
	ApplicationInit(&app);
	ApplicationRun(&app);
	ApplicationShutdown(&app);
	return 0;
}
