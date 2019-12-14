#include <stdio.h>
#include <iostream>
#include "tinyxml.h"
#include <string>

using namespace std;

void main()
{
	float offsetLeft, offsetRight;
	float screenWidth;
	float gridPart;
	cout << "Input offset left: \n";
	cin >> offsetLeft;
	cout << "Input offset right: \n";
	cin >> offsetRight;
	cout << "Input Screen Width: \n";
	cin >> screenWidth;
	cout << "Inout Grid Part: \n";
	cin >> gridPart;
	cout << "offset left: " << offsetLeft << " offset right: " << offsetRight << " screen width: " << screenWidth << "\n";
	float gridSize = (screenWidth + offsetLeft + offsetRight) / gridPart;
	cout << "Your grid size is: " << gridSize << "\n";

	//setting
	int options = 1;
	while (options != 0)
	{
		cout << "Chon chuc nang\n";
		cout << "1. Ghi file grid\n";
		cout << "0. Thoat\n";
		cin >> options;
		if (options == 1)
		{

			string filepath;
			cout << "Nhap duong dan file: ";
			cin >> filepath;
			//
			TiXmlDocument mapObjects(filepath.c_str());
			if (!mapObjects.LoadFile())
			{
				cout << "ERROR READ XML";
			}
			else
			{
				cout << "READ FILE SUCCESS\n";
				// get info root
				TiXmlElement* root = mapObjects.RootElement();
				TiXmlElement* Objects = nullptr;
				TiXmlElement* Object = nullptr;
				for (Objects = root->FirstChildElement(); Objects != NULL; Objects = Objects->NextSiblingElement())
				{
					int id;
					float x, y, Width, Height;
					Objects->QueryIntAttribute("id", &id);
					for (Object = Objects->FirstChildElement(); Object != NULL; Object = Object->NextSiblingElement())
					{
						Object->QueryFloatAttribute("x", &x);
						Object->QueryFloatAttribute("y", &y);
						Object->QueryFloatAttribute("width", &Width);
						Object->QueryFloatAttribute("height", &Height);
						if (Width < 800)
						{
							if (Width > gridSize)
							{
								int nodeQuantity = ceil(Width / gridSize) * 2;
								float newWidth = Width / nodeQuantity;
								for (int i = 1; i < nodeQuantity; i++)
								{
									TiXmlElement* newObjects = new TiXmlElement("Object");
									newObjects->SetAttribute("x", x + i*newWidth);
									newObjects->SetAttribute("y", y);
									newObjects->SetAttribute("width", newWidth);
									newObjects->SetAttribute("height", Height);
									Objects->LinkEndChild(newObjects);
								}
								Object->SetAttribute("width", newWidth);
							}
						}
						int grid = floor((x / gridSize));
						if (id == -99)
							grid = -1;
						if (grid < -1)
						{
							grid = -1;
						}
						Object->SetAttribute("Grid", grid);
					}
				}
				mapObjects.SaveFile();
				cout << "Tinh grid cho file thanh cong\n";
			}

		}

	}


	system("pause");
}