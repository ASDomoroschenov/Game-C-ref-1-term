#include "StartForm.h"
#include "GameForm.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
void main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	TicTacToeGame::StartForm form;
	Application::Run(% form);
}

System::Void TicTacToeGame::StartForm::оПрограммеToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	MessageBox::Show("Данная программа создана на основе игры <<Крестики-нолики>>", "О программе");
}

System::Void TicTacToeGame::StartForm::выходToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	Application::Exit();
}

System::Void TicTacToeGame::StartForm::buttonStartGame_Click(System::Object^ sender, System::EventArgs^ e)
{

	int indexGameMode = listBoxGameMode->SelectedIndex;
	if (indexGameMode == -1) {
		MessageBox::Show("Вы не выбрали режим игры!", "Внимание!");
		return;
	}

	int size;
	size = Convert::ToInt32(numericUpDownSizeMap->Value);

	numericUpDownLength->Maximum = size;
	int length = Convert::ToInt32(numericUpDownLength->Value);

	GameForm^ form = gcnew GameForm();
	form->rows = size;
	form->columns = size;
	form->length = length;
	form->selectedGameMode = indexGameMode;
	form->Show();
	this->Hide();
}