#include "menu.h"
#include "settings.h"
#include "functions.h"
#include "imguipp.h"
#include "icons.h"
#include "memory.h"
#include <Windows.h>
#include <iostream>
#include "externvar.h"
#include <fstream>
#pragma warning(disable : 4996)


// cheat vars
bool BrowserOpen = false;
std::string SelectedFile;
const char* ConData = "NULL";

const char* InfoText = "8==D MIU Menu, By Addison Sawyer C==8";
const char* InfoText6 = "::Pointers::";
const char* InfoText7 = "Module Base Address -> mono-2.0-bdwgc.dll";
const char* InfoText8 = "Static Ptr Base Address -> 0x00494A90";
const char* InfoText9 = "::Offsets::";
const char* InfoText10 = "Player | [Byte4] | 0xCE8, 0xA20";
const char* InfoText11 = "Health Maximum | [Float] | 0xE58, 0xEF4";
const char* InfoText12 = "Sheild Maximum | [Float] | 0xC98, 0x9C0";
const char* InfoText13 = "Stamina Maximum | [Float] | 0xEA0, 0xFC0";
const char* InfoText14 = "Hunger Maximum | [Float] | 0xEA0, 0xFD0";
const char* InfoText15 = "Current Health | [Byte4] | 0xEA0, 0xFB0";
const char* InfoText16 = "Current Sheild | [Byte4] | 0xC98, 0x9BC";
const char* InfoText17 = "Current Stamina | [Byte4] | 0xEA0, 0xFC8";
const char* InfoText18 = "Current Hunger | [Byte4] | 0xC98, 0x9CC";

static float TitleColor[] = { 1.f, .5f, .25f, 1.f };
static float BttnColor[] = { 0.121f, 0.117f, 0.121f, 1.f };
static float BttnHvrColor[] = { 0.160f, 0.156f, 0.160f, 1.f };
static float FrameBackGround[] = { 0.145f, 0.141f, 0.145f, 1.f };
static float CheckBoxColor[] = { 1.f, 0.396f, 0.207f, 1.f };
static float SliderColor[] = { 0.298f, 0.298f, 0.298f, 1.f};
static float SliderGrabColor[] = { 0.298f, 0.298f, 0.298f, 1.f };

int MaxHealth = 100;
int MaxSheild = 0;
int MaxStamina = 100;
int MaxHunger = 100;
int Health = 1065353216;
int Shield = 1065353216;
int Stamina = 1065353216;
int Hunger = 1065353216;
bool Enabled = true;

bool loadConfig()
{
	ConData = "We made it";
	std::ifstream in(SelectedFile);
	ConData = SelectedFile.c_str();

	if (!in.is_open())
	{
		//ConData = "Hello World";
		return false;
	}

	std::string param;
	float value;

	while (!in.eof())
	{
		in >> param;
		in >> value;


		if (param == "TITLE_COLOR_R")
		{
			TitleColor[0] = value;
		}
		else if (param == "TITLE_COLOR_G")
		{
			TitleColor[1] = value;
		}
		else if (param == "TITLE_COLOR_B")
		{
			TitleColor[2] = value;
		}
		else if (param == "TITLE_COLOR_A")
		{
			TitleColor[3] = value;
		}
		else if (param == "BTTN_COLOR_R")
		{
			BttnColor[0] = value;
		}
		else if (param == "BTTN_COLOR_G")
		{
			BttnColor[1] = value;
		}
		else if (param == "BTTN_COLOR_B")
		{
			BttnColor[2] = value;
		}
		else if (param == "BTTN_COLOR_A")
		{
			BttnColor[3] = value;
		}
		else if (param == "BTTN_HVR_COLOR_R")
		{
			BttnHvrColor[0] = value;
		}
		else if (param == "BTTN_HVR_COLOR_G")
		{
			BttnHvrColor[1] = value;
		}
		else if (param == "BTTN_HVR_COLOR_B")
		{
			BttnHvrColor[2] = value;
		}
		else if (param == "BTTN_HVR_COLOR_A")
		{
			BttnHvrColor[3] = value;
		}
		else if (param == "SLIDER_COLOR_R")
		{
			SliderColor[0] = value;
		}
		else if (param == "SLIDER_COLOR_G")
		{
			SliderColor[1] = value;
		}
		else if (param == "SLIDER_COLOR_B")
		{
			SliderColor[2] = value;
		}
		else if (param == "SLIDER_COLOR_A")
		{
			SliderColor[3] = value;
		}
		else if (param == "SLIDER_GRAB_COLOR_R")
		{
			SliderGrabColor[0] = value;
		}
		else if (param == "SLIDER_GRAB_COLOR_G")
		{
			SliderGrabColor[1] = value;
		}
		else if (param == "SLIDER_GRAB_COLOR_B")
		{
			SliderGrabColor[2] = value;
		}
		else if (param == "SLIDER_GRAB_COLOR_A")
		{
			SliderGrabColor[3] = value;
		}
	}
	in.close();
	Settings::Tab = 2;
	return true;
}

bool saveConfig()
{
	std::string SettingText = "";
	int number = rand() % 10000;
	std::string config = "Config"+ std::to_string(number) + ".config";
	FILE* pFile = fopen(config.c_str(), "a");
	for (int i = 0; i < 4; i++)
	{
		std::string TitleColorConfig = std::to_string(TitleColor[i]);

		switch (i)
		{
			case 0: SettingText = "TITLE_COLOR_R " + TitleColorConfig; break;
			case 1: SettingText = "TITLE_COLOR_G " + TitleColorConfig; break;
			case 2: SettingText = "TITLE_COLOR_B " + TitleColorConfig; break;
			case 3: SettingText = "TITLE_COLOR_A " + TitleColorConfig; break;
		}
		
		fprintf(pFile, "%s\n", SettingText.c_str());
	}
	for (int i = 0; i < 4; i++)
	{
		std::string BttnColorConfig = std::to_string(BttnColor[i]);
		switch (i)
		{
			case 0: SettingText = "BTTN_COLOR_R " + BttnColorConfig; break;
			case 1: SettingText = "BTTN_COLOR_G " + BttnColorConfig; break;
			case 2: SettingText = "BTTN_COLOR_B " + BttnColorConfig; break;
			case 3: SettingText = "BTTN_COLOR_A " + BttnColorConfig; break;
		}
		fprintf(pFile, "%s\n", SettingText.c_str());
	}
	for (int i = 0; i < 4; i++)
	{
		std::string BttnHvrColorConfig = std::to_string(BttnHvrColor[i]);

		switch (i)
		{
			case 0: SettingText = "BTTN_HVR_COLOR_R " + BttnHvrColorConfig; break;
			case 1: SettingText = "BTTN_HVR_COLOR_G " + BttnHvrColorConfig; break;
			case 2: SettingText = "BTTN_HVR_COLOR_B " + BttnHvrColorConfig; break;
			case 3: SettingText = "BTTN_HVR_COLOR_A " + BttnHvrColorConfig; break;
		}
		fprintf(pFile, "%s\n", SettingText.c_str());
	}
	for (int i = 0; i < 4; i++)
	{
		std::string SliderColorConfig = std::to_string(SliderColor[i]);

		switch (i)
		{
			case 0: SettingText = "SLIDER_COLOR_R " + SliderColorConfig; break;
			case 1: SettingText = "SLIDER_COLOR_G " + SliderColorConfig; break;
			case 2: SettingText = "SLIDER_COLOR_B " + SliderColorConfig; break;
			case 3: SettingText = "SLIDER_COLOR_A " + SliderColorConfig; break;
		}
		fprintf(pFile, "%s\n", SettingText.c_str());
	}
	for (int i = 0; i < 4; i++)
	{
		std::string SliderGrabColorConfig = std::to_string(SliderGrabColor[i]);

		switch (i)
		{
			case 0: SettingText = "SLIDER_GRAB_COLOR_R " + SliderGrabColorConfig; break;
			case 1: SettingText = "SLIDER_GRAB_COLOR_G " + SliderGrabColorConfig; break;
			case 2: SettingText = "SLIDER_GRAB_COLOR_B " + SliderGrabColorConfig; break;
			case 3: SettingText = "SLIDER_GRAB_COLOR_A " + SliderGrabColorConfig; break;
		}
		fprintf(pFile, "%s\n", SettingText.c_str());
	}
	fclose(pFile);
	return true;
}

bool FileBrowse()
{
	if (BrowserOpen == true)
	{
		ImGui::FileBrowser fileDialog;

		// (optional) set browser properties
		fileDialog.SetTitle("File Browser");
		fileDialog.SetTypeFilters({ ".config" });
		fileDialog.Open();
		fileDialog.Display();
		if (fileDialog.HasSelected())
		{
			SelectedFile = fileDialog.GetSelected().string();
			BrowserOpen = false;
			loadConfig();
		}
	}

}

void Menu::Render()
{
	// Grab our Application
	DWORD procId = GetProcId(L"Muck.exe");

	uintptr_t moduleBase = GetModuleBaseAddress(procId, L"mono-2.0-bdwgc.dll");

	HANDLE hProcess = 0;

	hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);

	uintptr_t dynamicPtrBaseAddr = moduleBase + 0x00494A90; // This is the Player Address
	// Keep Max Cheats Out Here to Prevent Revert
	// Max Shield Cheat
	std::vector<unsigned int> shieldMaxOffset = { 0xC98, 0x9C0 };
	uintptr_t shieldMaxAddr = FindDMAAddy(hProcess, dynamicPtrBaseAddr, shieldMaxOffset);

	int currentMaxSheild = 0;

	ReadProcessMemory(hProcess, (BYTE*)shieldMaxAddr, &currentMaxSheild, sizeof(currentMaxSheild), nullptr);

	int newMaxSheild = MaxSheild;

	WriteProcessMemory(hProcess, (BYTE*)shieldMaxAddr, &newMaxSheild, sizeof(newMaxSheild), nullptr);
	//End of Max Shield

	// Max Health Cheat
	std::vector<unsigned int> healthMaxOffset = { 0xE58, 0xEF4 };
	uintptr_t healthMaxAddr = FindDMAAddy(hProcess, dynamicPtrBaseAddr, healthMaxOffset);

	int currentMaxHealth = 0;

	ReadProcessMemory(hProcess, (BYTE*)healthMaxAddr, &currentMaxHealth, sizeof(currentMaxHealth), nullptr);

	int newMaxHealth = MaxHealth;

	WriteProcessMemory(hProcess, (BYTE*)healthMaxAddr, &newMaxHealth, sizeof(newMaxHealth), nullptr);
	//End of Max Health

	// Max Stamina Cheat
	std::vector<unsigned int> MaxStaminaOffset = { 0xEA0, 0xFC8 };
	uintptr_t MaxStaminaAddr = FindDMAAddy(hProcess, dynamicPtrBaseAddr, MaxStaminaOffset);

	int currentMaxStamina = 0;

	ReadProcessMemory(hProcess, (BYTE*)MaxStaminaAddr, &currentMaxStamina, sizeof(currentMaxStamina), nullptr);

	int newMaxStamina = MaxStamina;

	WriteProcessMemory(hProcess, (BYTE*)MaxStaminaAddr, &newMaxStamina, sizeof(newMaxStamina), nullptr);
	// End Max Stamina Cheat

	// Max Hunger Cheat
	std::vector<unsigned int> MaxHungerOffset = { 0xEA0, 0xFD0 };
	uintptr_t MaxHungerAddr = FindDMAAddy(hProcess, dynamicPtrBaseAddr, MaxHungerOffset);

	int currentMaxHunger = 0;

	ReadProcessMemory(hProcess, (BYTE*)MaxHungerAddr, &currentMaxHunger, sizeof(currentMaxHunger), nullptr);

	int newMaxHunger = MaxHunger;

	WriteProcessMemory(hProcess, (BYTE*)MaxHungerAddr, &newMaxHunger, sizeof(newMaxHunger), nullptr);
	// End Max Stamina Cheat

	// Start Our Render
	ImGui::Columns(2);
	ImGui::SetColumnOffset(1, 230);

	{
		//Left side

		static ImVec4 active = imguipp::to_vec4(41, 40, 41, 255);
		static ImVec4 inactive = imguipp::to_vec4(31, 30, 31, 255);

		ImGui::PushStyleColor(ImGuiCol_Button, Settings::Tab == 1 ? active : inactive);
		if (ImGui::Button(ICON_FA_CODE " Cheats", ImVec2(230 - 15, 41)))
			Settings::Tab = 1;

		ImGui::Spacing();
		ImGui::PushStyleColor(ImGuiCol_Button, Settings::Tab == 2 ? active : inactive);
		if (ImGui::Button(ICON_FA_DOWNLOAD " Theme", ImVec2(230 - 15, 41)))
			Settings::Tab = 2;

		ImGui::Spacing();
		ImGui::PushStyleColor(ImGuiCol_Button, Settings::Tab == 3 ? active : inactive);
		if (ImGui::Button(ICON_FA_BOOK " Info", ImVec2(230 - 15, 41)))
			Settings::Tab = 3;

		ImGui::Spacing();
		ImGui::PushStyleColor(ImGuiCol_Button, Settings::Tab == 5 ? active : inactive);
		if (ImGui::Button(ICON_FA_EJECT " Exit", ImVec2(230 - 15, 41)))
			Settings::Tab = 5;

		ImGui::PopStyleColor(4);

		ImGui::SetCursorPosY(ImGui::GetWindowHeight() - 30);
		imguipp::center_text_ex("Made By Addison Sawyer", 230, 1, false);
	}

	ImGui::NextColumn();

	//Right side
	{

		if (Settings::Tab == 1)
		{
			// put maxes outside the execute func they need to be permanant
			ImGui::SliderInt("Max Health", &MaxHealth, 1, 10000);
			ImGui::SliderInt("Max Shield", &MaxSheild, 0, 10000);
			ImGui::SliderInt("Max Stamina", &MaxStamina, 0, 10000);
			ImGui::SliderInt("Max Hunger", &MaxHunger, 0, 10000);
			ImGui::SliderInt("Health(Byte4)", &Health, 1065353216, 1176256512);
			ImGui::SliderInt("Shield(Byte4)", &Shield, 1065353216, 1176256512);
			ImGui::SliderInt("Stamina(Byte4)", &Stamina, 1065353216, 1176256512);
			ImGui::SliderInt("Hunger(Byte4)", &Hunger, 1065353216, 1176256512);
			if (ImGui::Button("Execute Cheats", ImVec2(200, 35)))
			{
				// Health Cheat
				std::vector<unsigned int> HealthOffset = { 0xEA0, 0xFB0 };
				uintptr_t HealthAddr = FindDMAAddy(hProcess, dynamicPtrBaseAddr, HealthOffset);

				int currentHealth = 0;

				ReadProcessMemory(hProcess, (BYTE*)HealthAddr, &currentHealth, sizeof(currentHealth), nullptr);

				int newHealth = Health;

				WriteProcessMemory(hProcess, (BYTE*)HealthAddr, &newHealth, sizeof(newHealth), nullptr);
				// End Health Cheat

				// Shield Cheat
				std::vector<unsigned int> shieldOffset = { 0xC98, 0x9BC };
				uintptr_t shieldAddr = FindDMAAddy(hProcess, dynamicPtrBaseAddr, shieldOffset);

				int currentSheild = 0;

				ReadProcessMemory(hProcess, (BYTE*)shieldAddr, &currentSheild, sizeof(currentSheild), nullptr);

				int newSheild = Shield;

				WriteProcessMemory(hProcess, (BYTE*)shieldAddr, &newSheild, sizeof(newSheild), nullptr);
				// End Sheild Cheat

				// Stamina Cheat
				std::vector<unsigned int> StaminaOffset = { 0xDC0, 0xD84 };
				uintptr_t StaminaAddr = FindDMAAddy(hProcess, dynamicPtrBaseAddr, StaminaOffset);

				int currentStamina = 0;

				ReadProcessMemory(hProcess, (BYTE*)StaminaAddr, &currentStamina, sizeof(currentStamina), nullptr);

				int newStamina = Stamina;

				WriteProcessMemory(hProcess, (BYTE*)StaminaAddr, &newStamina, sizeof(newStamina), nullptr);
				// End Stamina Cheat

				// Stamina Cheat
				std::vector<unsigned int> HungerOffset = { 0xC98, 0x9CC };
				uintptr_t HungerAddr = FindDMAAddy(hProcess, dynamicPtrBaseAddr, HungerOffset);

				int currentHunger = 0;

				ReadProcessMemory(hProcess, (BYTE*)HungerAddr, &currentHunger, sizeof(currentHunger), nullptr);

				int newHunger = Hunger;

				WriteProcessMemory(hProcess, (BYTE*)HungerAddr, &newHunger, sizeof(newHunger), nullptr);
				// End Stamina Cheat
			}


		}
		else if (Settings::Tab == 2)
		{
			ImGui::ColorEdit4("Title Color", TitleColor);
			ImGui::ColorEdit4("Button Color", BttnColor); // Doesnt Change Bttn Color IDK Why
			ImGui::ColorEdit4("Button Hover Color", BttnHvrColor);
			ImGui::ColorEdit4("Slider Color", SliderColor);
			ImGui::ColorEdit4("Slider Grab Color", SliderGrabColor);
			if (ImGui::Button("Save Config", ImVec2(200, 35)))
			{
				saveConfig();
			}
			if (ImGui::Button("Load Config", ImVec2(200, 35)))
			{
				BrowserOpen = true;
				if (BrowserOpen == true)
				{
					Settings::Tab = 4;
				}
				
			}
		}
		else if (Settings::Tab == 3)
		{
			ImGui::Text(InfoText);
			ImGui::Text(InfoText6);
			ImGui::Text(InfoText7);
			ImGui::Text(InfoText8);
			ImGui::Text(InfoText9);
			ImGui::Text(InfoText10);
			ImGui::Text(InfoText11);
			ImGui::Text(InfoText12);
			ImGui::Text(InfoText13);
			ImGui::Text(InfoText14);
			ImGui::Text(InfoText15);
			ImGui::Text(InfoText16);
			ImGui::Text(InfoText17);
			ImGui::Text(InfoText18);
		}
		else if (Settings::Tab == 4)
		{
			ImGui::Text(ConData);
			FileBrowse();
		}
		else if (Settings::Tab == 5)
		{
			Enabled = !Enabled;
		}
	}
}

void Menu::Theme()
{
	ImGuiStyle* style = &ImGui::GetStyle();

	style->WindowBorderSize = 0;
	style->WindowTitleAlign = ImVec2(0.5, 0.5);
	style->WindowMinSize = ImVec2(900, 430);

	style->FramePadding = ImVec2(8, 6);
	style->Colors[ImGuiCol_TitleBg] = ImColor(TitleColor[0], TitleColor[1], TitleColor[2], TitleColor[3]);
	style->Colors[ImGuiCol_TitleBgActive] = ImColor(TitleColor[0], TitleColor[1], TitleColor[2], TitleColor[3]);
	style->Colors[ImGuiCol_TitleBgCollapsed] = ImColor(0, 0, 0, 130);

	style->Colors[ImGuiCol_Button] = ImColor(BttnColor[0], BttnColor[1], BttnColor[2], BttnColor[3]);
	style->Colors[ImGuiCol_ButtonActive] = ImColor(BttnHvrColor[0], BttnHvrColor[1], BttnHvrColor[2], BttnHvrColor[3]);
	style->Colors[ImGuiCol_ButtonHovered] = ImColor(BttnHvrColor[0], BttnHvrColor[1], BttnHvrColor[2], BttnHvrColor[3]);

	style->Colors[ImGuiCol_Separator] = ImColor(70, 70, 70, 255);
	style->Colors[ImGuiCol_SeparatorActive] = ImColor(76, 76, 76, 255);
	style->Colors[ImGuiCol_SeparatorHovered] = ImColor(76, 76, 76, 255);

	style->Colors[ImGuiCol_FrameBg] = ImColor(FrameBackGround[0], FrameBackGround[1], FrameBackGround[2], FrameBackGround[3]);
	style->Colors[ImGuiCol_FrameBgActive] = ImColor(FrameBackGround[0], FrameBackGround[1], FrameBackGround[2], FrameBackGround[3]);
	style->Colors[ImGuiCol_FrameBgHovered] = ImColor(FrameBackGround[0], FrameBackGround[1], FrameBackGround[2], FrameBackGround[3]);

	style->Colors[ImGuiCol_SliderGrab] = ImColor(SliderColor[0], SliderColor[1], SliderColor[2], SliderColor[3]);
	style->Colors[ImGuiCol_SliderGrabActive] = ImColor(SliderGrabColor[0], SliderGrabColor[1], SliderGrabColor[2], SliderGrabColor[3]);
}
