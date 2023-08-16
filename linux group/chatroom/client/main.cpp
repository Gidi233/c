#include "UI.hpp"
#include "client.hpp"
int main(int argc, char *argv[])
{
	if (argc == 1 || argc == 3)
	{
		if (argc == 1)
		{
			client cil;
			Main_UI_First();
		}
		if (argc == 3)
		{
			client cli(argv[1], argv[2]);
			Main_UI_First();
		}
	}
	else
		cout << "输的什么东西";
	exit(1);
	// return 0;
}
