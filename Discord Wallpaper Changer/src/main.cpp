#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <Windows.h>
int main()
{
	::ShowWindow(::GetConsoleWindow(), 0);
	std::ifstream linksFile("links.txt");
	std::ifstream info("info.txt");
	std::vector<std::string> links, codeLines;
	int wait;
	std::string srcPath;
	std::string line;

	if (!linksFile)
		std::cout << "Links cannot be opened" << std::endl;

	//Getting the info
	std::getline(info, line);
	srcPath = line;
	std::getline(info, line);
	std::stringstream ss;
	ss << line;
	ss >> wait;
	std::cout << wait << std::endl;
	std::ifstream src(srcPath);

	//Getting the links
	while (std::getline(linksFile, line))
	{
		links.push_back(line);
	}
	linksFile.close();
	//Getting the CSS source code
	while (std::getline(src, line))
	{
		codeLines.push_back(line);
	}
	src.close();
	int counter = 0;
	std::fstream osrc;
	while (true)
	{
		for (int i = 0; i < codeLines.size(); i++)
		{
			if (codeLines[i].find("MAIN") != std::string::npos)
			{
				codeLines[i] = "--background:url(" + links[counter % links.size()] + ");/*MAIN general background image*/";
			}
		}
		counter++;
		osrc.open(srcPath, std::ios::out);
		if (!osrc.good())
			std::cout << "Cannot open src file" << std::endl;
		osrc.seekp(0);
		for (auto a : codeLines)
		{
			osrc << a << "\n";
		}
		osrc.close();
		std::this_thread::sleep_for(std::chrono::seconds(wait));
	}

	return 0;
}