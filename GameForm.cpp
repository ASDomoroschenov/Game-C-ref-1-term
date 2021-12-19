#include "GameForm.h"
#include "StartForm.h"

enum GameMode {
    PvP = 0,
    PvE
} gameMode;

GameMap map;
Gamer player1;
Gamer player2;
GamerStatus currentPlayer;
SizeMap selectedCellPlayer;

bool canPlay;
bool endGame;

std::vector<SizeMap> allMoves;
int currentMoves;

System::Void TicTacToeGame::GameForm::GameForm_Load(System::Object^ sender, System::EventArgs^ e)
{
    if (selectedGameMode == 0) {
        gameMode = PvP;
    }
    else {
        gameMode = PvE;
    }

    NewGame();
}

System::Void TicTacToeGame::GameForm::новаяИграToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
    if (MessageBox::Show("Продолжить?", "Внимание!", MessageBoxButtons::YesNo) == Windows::Forms::DialogResult::Yes) {
        NewGame();
    }
}

System::Void TicTacToeGame::GameForm::вернутьсяToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
    if (MessageBox::Show("Продолжить?", "Внимание!", MessageBoxButtons::YesNo) == Windows::Forms::DialogResult::Yes) {
        StartForm^ form = gcnew StartForm();
        form->Show();
        this->Hide();
    }
}

System::Void TicTacToeGame::GameForm::оПрограммеToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
    MessageBox::Show("Программа реализует игру <<Крестики-нолики>> стандартного типа для двух игроков и против компьютера!", "О программе");
}

System::Void TicTacToeGame::GameForm::выходToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
    if (MessageBox::Show("Продолжить?", "Внимание!", MessageBoxButtons::YesNo) == Windows::Forms::DialogResult::Yes) {
        Application::Exit();
    }
}

System::Void TicTacToeGame::GameForm::dataGridView_CellContentClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e)
{
    auto senderGrid = (DataGridView^)sender;

    selectedCellPlayer.x = e->RowIndex;
    selectedCellPlayer.y = e->ColumnIndex;
    
    SetPositionPlayer(selectedCellPlayer);
}

System::Void TicTacToeGame::GameForm::вклВыклЗвукToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
    return System::Void();
}

void TicTacToeGame::GameForm::GameLogic()
{
    if (gameMode == PvE) {
        if (currentPlayer == Computer) {
            StepAI();
        }

        UpDate();
    }
}

void TicTacToeGame::GameForm::UpDate()
{
    int state_game = map.CheckingWin();

    if (endGame)
        return;

    if (state_game == 1) {
        if (gameMode == PvP) {
            MessageBox::Show("Поздравляем Игрока1 с победой!!!", "Победа!");
        }
        else {
            MessageBox::Show("Поздравляем Игрока с победой!!!", "Победа!");
        }

        UpdateGameGrid();

        endGame = true;
    }
    else {
        if (state_game == 2) {
            if (gameMode == PvP) {
                MessageBox::Show("Поздравляем Игрока2 с победой!!!", "Победа!");
            }
            else {
                MessageBox::Show("Поздравляем Компьютера с победой!!!", "Победа!");
            }

            UpdateGameGrid();

            endGame = true;
        }
        else {
            if (state_game == 3) {
                MessageBox::Show("Победила дружба!!!", "Ничья!");
                UpdateGameGrid();

                endGame = true;
            }
        }
    }

    if (endGame) {
        if (MessageBox::Show("Запустить новую игру?", "Внимание", MessageBoxButtons::YesNo) == Windows::Forms::DialogResult::Yes) {
            NewGame();
        }
        return;
    }

    if (gameMode == PvE) {
        if (currentPlayer == Computer) {
            Status->Text = "Ход: Игрока!";
            currentPlayer = Player;
            return;
        }
        else {
            Status->Text = "Ход: Компьютера!";
            currentPlayer = Computer;

            GameLogic();
            UpdateGameGrid();
            return;
        }
    }
    else {
        if (currentPlayer == Player1) {
            Status->Text = "Ход: 0!";
            currentPlayer = Player2;
        }
        else {
            Status->Text = "Ход: X";
            currentPlayer = Player1;
        }
    }
    
    GameLogic();
    UpdateGameGrid();
}

void TicTacToeGame::GameForm::NewGame()
{
    map.SetMap(rows, columns, length);
    rand = gcnew Random();
    endGame = false;

    CreateGameGrid(map.GetSize());
    currentMoves = 0;
    allMoves.clear();
    SizeMap buf;
    for (int i = 0; i < map.GetSize().x; i++) {
        for (int j = 0; j < map.GetSize().x; j++) {
            buf.x = i;
            buf.y = j;

            allMoves.push_back(buf);
        }
    }

    int num_mixing = rand->Next(1, 10);

    for (int i = 0; i < num_mixing; i++)
        std::random_shuffle(allMoves.begin(), allMoves.end());

    int state_gamer = rand->Next(1, 3);

    if (state_gamer == 1) {
        if (gameMode == PvE) {
            player1.SetField(Player, 1);
            player2.SetField(Computer, 2);

            Status->Text = "Ход: Игрока!";

            currentPlayer = Player;
        }
        else {
            player1.SetField(Player1, 1);
            player2.SetField(Player2, 2);

            Status->Text = "Ход: X!";

            currentPlayer = Player1;
        }
    }
    else {
        if (state_gamer == 2) {
            if (gameMode == PvE) {
                player1.SetField(Player, 1);
                player2.SetField(Computer, 2);

                Status->Text = "Ход: Компьютера!";

                currentPlayer = Player;

                GameLogic();
                UpdateGameGrid();
            }
            else {
                player1.SetField(Player1, 1);
                player2.SetField(Player2, 2);

                Status->Text = "Ход: 0!";

                currentPlayer = Player2;
            }
        }
        else {
            MessageBox::Show("Ошибка генерации первоначального выбора игрока!", "Ошибка");
            return;
        }
    }

}

void TicTacToeGame::GameForm::StepAI()
{
    if (currentMoves < allMoves.size()) {
        if (map.IsEmpty(allMoves[currentMoves])) {
            map.SetPosition(allMoves[currentMoves], player2.GetMark());
            currentMoves++;
        }
        else {
            currentMoves++;
            StepAI();
        }
    }
}

void TicTacToeGame::GameForm::UpdateGameGrid()
{
    for (int i = 0; i < map.GetSize().x; i++) {
        for (int j = 0; j < map.GetSize().y; j++) {
            if (!map.IsEmpty(i, j)) {
                if (map.GetValue(i, j) == 1) {
                    dataGridView->Rows[i]->Cells[j]->Value = "X";
                }
                else {
                    dataGridView->Rows[i]->Cells[j]->Value = "0";
                }
            }
        }
    }
}

void TicTacToeGame::GameForm::CreateGameGrid(SizeMap size)
{
    dataGridView->Rows->Clear();
    dataGridView->Columns->Clear();

    System::Drawing::Font^ font = gcnew System::Drawing::Font("Microsoft Sans Serif", 14);
    dataGridView->DefaultCellStyle->Font = font;
    dataGridView->ColumnHeadersDefaultCellStyle->Font = font;
    dataGridView->RowHeadersDefaultCellStyle->Font = font;

    for (int i = 0; i < size.x; i++) {
        DataGridViewButtonColumn^ column = gcnew DataGridViewButtonColumn();
        column->HeaderCell->Value = Convert::ToString(i + 1);
        column->Name = "column" + i;
        column->Width = 50;

        dataGridView->Columns->Add(column);
    }

    for (int i = 0; i < size.y; i++) {
        dataGridView->Rows->Add();
        dataGridView->Rows[i]->HeaderCell->Value = Convert::ToString(i + 1);
        dataGridView->Rows[i]->Height = 50;
    }
}

System::Void TicTacToeGame::GameForm::SetPositionPlayer(SizeMap cell)
{
    if (gameMode == PvE) {
        if (currentPlayer == Player) {
            if (!map.SetPosition(cell, player1.GetMark())) {
                MessageBox::Show("Данная позиция занята!", "Внимание");
                return;
            }
        }
        else {
            MessageBox::Show("Еще не ваша очередь!", "Внимание");
            return;
        }
    }
    else {
        if (currentPlayer == Player1) {
            if (!map.SetPosition(cell, player1.GetMark())) {
                MessageBox::Show("Данная позиция занята!", "Внимание");
                return;
            }
        }
        else {
            if (!map.SetPosition(cell, player2.GetMark())) {
                MessageBox::Show("Данная позиция занята!", "Внимание");
                return;
            }
        }
    }

   UpDate();
}
