#include "HoggleFunctions.h"

int main()
{
    Lexicon lex("lexicon.dat");
    Lexicon*ptr=&lex;
    int pos=0;
    bool wordOnBoard=false;
    int randDie=0;
    int score=0;
    vector<int>rows;
    vector<int>columns;
    string points;
    vector<string>dice;
    vector<string>tempdice;
    vector<string>playedWords;
    string go;
    bool keepGoing=true;
    int eraseint=0;
    string myVariable;
    string temp;
    string currentWord ;
    ifstream fin;
    string tempCurrent;
    fin.open("dice.txt");
    for (int i=0; i<19; i++)
    {
        fin>>temp;
        myVariable+=temp;
    }
    fin.close();

    for (int i=0; i<19; i++)
    {
        pos=i*6;
        temp=myVariable.substr(pos,6);
        dice.push_back(temp);
    }

    // Here is a double for loop that iterates through all dice
    // on the board
    while(keepGoing)
    {
        /// This function draws and clears the board framework
        DrawBoard();
        playedWords.clear();

        int j=0;
        tempdice=dice;
        for (int r = 0; r < 5; r++)
        {
            for (int c = 0; c < DiceInRow(r); c++)
            {
                eraseint=RandomInt(0,18-j);
                temp=tempdice[eraseint];
                LabelHex(r, c, temp[RandomInt(0,5)]);
                tempdice.erase(tempdice.begin() + eraseint);
                j++;
            }
        }

        UpdateDisplay();
        while(true)
        {
            wordOnBoard=false;
            PrintMessage("--- Human's Turn ---\n");

            // Getting input onscreen
            PrintMessage ("Enter a word: ");
            currentWord = BoardGetLine();
            if (currentWord=="")
            {
                for (int r = 0; r < 5; r++)
                {
                    for (int c = 0; c < DiceInRow(r); c++)
                    {
                        string tempword="";
                        rows.push_back(r);
                        columns.push_back(c);
                        tempword=tempword+LetterAt(r,c);
                        ComputerTurn(r,c,rows,columns,tempword,ptr,playedWords);
                        rows.clear();
                        columns.clear();
                    }
                }
                break;
            }
            if(find(playedWords.begin(),playedWords.end(),currentWord)!=playedWords.end())
            {
                PrintMessage("You already played that word.\n");
                continue;
            }
            if(currentWord.length()<3)
            {
                PrintMessage("Words must be at least 3 letters long.\n");
                continue;
            }
            tempCurrent=currentWord;
            for (int r = 0; r < 5; r++)
            {
                if(wordOnBoard)
                {
                    break;
                }
                for (int c = 0; c < DiceInRow(r); c++)
                {
                    if(LetterAt(r,c)==currentWord[0])
                    {
                        rows.push_back(r);
                        columns.push_back(c);
                        tempCurrent=currentWord;
                        if(WordSolver(r,c,rows,columns,tempCurrent.substr(1)))
                        {
                            wordOnBoard=true;
                            break;
                        }
                        else
                        {
                            rows.clear();
                            columns.clear();
                        }

                    }
                }
            }

            if(wordOnBoard==true)
            {
                if(lex.containsWord(currentWord))
                {
                    for(int i=0; i<rows.size(); i++)
                    {
                        HighlightHex(rows[i], columns[i], true); // highlighting on
                        Pause(0.1);
                        HighlightHex(rows[i], columns[i], false); // highlighting off
                    }
                    RecordNewWord(currentWord, Human);
                    score=1+(currentWord.length()-3);
                    points= NumberToString(score);
                    PrintMessage ("Good! You gain "+points+" points for '"+currentWord+"'.\n");
                    playedWords.push_back(currentWord);
                }
                else
                {
                    for(int i=0; i<rows.size(); i++)
                    {
                        HighlightHex(rows[i], columns[i], true); // highlighting on
                        Pause(0.1);
                        HighlightHex(rows[i], columns[i], false); // highlighting off
                    }
                    PrintMessage ("'"+currentWord+"' is on the board, but is not an English word.\n");
                }
            }
            else
            {
                PrintMessage ("'"+currentWord+"' cannot be formed on the board.\n");
            }


            rows.clear();
            columns.clear();

        }

        while(true)
        {
            PrintMessage("Play again (Y/N): ");
            go=BoardGetLine();
            if(go=="y"||go=="Y")
            {
                keepGoing=true;
                break;
            }
            else if(go=="n"||go=="N")
            {
                keepGoing=false;

                break;
            }
            else
            {
                continue;
            }
        }
    }
}
