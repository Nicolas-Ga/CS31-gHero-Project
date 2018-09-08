#include <iostream>
#include <algorithm>
#include <cctype>
#include <string>
using namespace std;

bool hasCorrectSyntax(string);

bool isTranslateable(string);

bool isColor(char);

char colorStore(char);

bool sustainDigitCheck(string, int);

bool sustainInterruptionCheck(string, int);

bool prematureEnd(string, int);

int translateSong(string, string&, int&);

int badBeatFinder(string);

string createTranslation(string);

int main()
{
	string s = "";
	string instrs = "smh";
	int badb = -999;
	cout << "Write song: ";
	getline(cin, s);
	cout << "Error Code: " << translateSong(s, instrs, badb) << endl;
	cout << "Translation: " << instrs << endl;
	cout << "Bad Beat: " << badb << endl;
}


bool hasCorrectSyntax(string song)
{
	for (int c = 0; c != song.size(); ++c) //goes through series of checks to see if entered song is syntacically correct
	{
		if (isColor(song[c]))
		{

			if (isdigit(song[c + 1]))
			{// is the song following proper sustain note syntax?


				if (isdigit(song[c + 2]))
				{ // check for proper two digit procedure

					if ((song[c + 3] == '/'))
					{
						c = c + 3; // move on past the slash
						continue;
					}

					else
					{
						return false;
					}
				}

				else if ((song[c + 2] == '/'))
				{
					c = c + 2; // move on past the slash
					continue;
				}

				else
				{
					return false;
				}
			}

			else if (song[c + 1] == '/') // is the song following normal note procedure?
			{
				++c; // move on past the slash
				continue;
			}
			else
			{
				return false;
			}

		}

		else if (song[c] == '/') //is there a pause here?
		{
			continue;
		}
		else
		{
			return false;
		}
	}

	return true;
}

bool isTranslateable(string song)
{
	for (int c = 0; c != song.size(); ++c) //goes through series of checks to see if entered song is syntacically correct
	{


		if (isColor(song[c]))
		{

			if (isdigit(song[c + 1]))
			{// is the song following proper sustain note syntax?

				int numBeat = song[c + 1];


				for (int k = 48; k < 57; k++)
				{
					if (k == numBeat)
					{
						numBeat = k - 48;
						break;
					}
				}


				if (isdigit(song[c + 2]))
				{ // check for proper two digit procedure

					numBeat = numBeat * 10;

					int numBeat1 = song[c + 2];


					for (int k = 48; k < 57; k++)
					{
						if (k == numBeat1)
						{
							numBeat1 = k - 48;
							break;
						}
					}

					numBeat = numBeat + numBeat1;

					int i = 3;
					for (; i - 3 < numBeat; i++)
					{

						if (song[c + i] == '/') // does song have the right # of slashes for sustain
						{
							continue;
						}
						else
						{
							return false;
						}
					}
					c = c + (numBeat + 1);
				}

				else if (numBeat == 1)
				{
					return false;
				}

				else if ((song[c + 2] == '/'))
				{
					int i = 2;
					for (; i - 2 < numBeat; i++)
					{
						if (song[c + i] == '/') // does song have the right # of slashes for sustain
						{
							continue;
						}
						else
						{
							return false;
						}
					}
					c = c + (numBeat + 1);
				}

				else
				{
					return false;
				}
			}
			else if (song[c + 1] == '/') // is the song following normal note procedure?
			{
				++c;
				continue;
			}
			else
			{
				return false;
			}
		}

		else if (song[c] == '/') //is there a pause here?
		{
			continue;
		}
		else
		{
			return false;
		}
	}
	return true;
}

bool isColor(char beat)
{
	//checks if note is a recognized color 
	if (beat == 'g' || beat == 'r' || beat == 'y' || beat == 'b'
		|| beat == 'o' || beat == 'G' || beat == 'R'
		|| beat == 'Y' || beat == 'B' || beat == 'O')
	{
		return true;
	}
	else
	{
		return false;
	}
}

char colorStore(char color)
{
	//returns color from entered song if there is a color
	if (color == 'g' || color == 'G')
		return 'g';
	else if (color == 'r' || color == 'R')
		return 'r';
	else if (color == 'y' || color == 'Y')
		return 'y';
	else if (color == 'b' || color == 'B')
		return 'b';
	else if (color == 'o' || color == 'O')
		return 'o';
	else
		return 'p';

}

bool sustainDigitCheck(string song, int badBeat)
{
	for (int c = 0; c != badBeat; ++c)
		//goes through series of checks to see 
		//if entered song does not have 1s or 0s
	{

		if (isColor(song[c]))
		{

			if (isdigit(song[c + 1]))
			{// is the song following proper sustain note syntax?

				int numBeat = song[c + 1];


				for (int k = 48; k < 57; ++k)
				{
					if (k == numBeat)
					{
						numBeat = k - 48;
						break;
					}
				}



				if (isdigit(song[c + 2]))
				{ // check for proper two digit procedure

					numBeat = numBeat * 10;

					int numBeat1 = song[c + 2];


					for (int k = 48; k < 57; ++k)
					{
						if (k == numBeat1)
						{
							numBeat1 = k - 48;
							break;
						}
					}

					numBeat = numBeat + numBeat1;


					if (numBeat == 0 || numBeat == 1)
					{
						return false;
					}

					int i = 3;

					c = c + (numBeat + 1);
				}

				else if (numBeat == 1 || numBeat == 0)
				{
					return false;
				}
			}

		}
	}
	return true;
}

bool sustainInterruptionCheck(string song, int badBeat)
{
	for (int c = 0; c != badBeat; ++c)
		//goes through series of checks to see 
		//if entered song interrupts its sustained notes with
		//something that is not a backslash
	{

		if (isColor(song[c]))
		{

			if (isdigit(song[c + 1]))
			{// is the song following proper sustain note syntax?

				int numBeat = song[c + 1];


				for (int k = 48; k < 57; ++k)
				{
					if (k == numBeat)
					{
						numBeat = k - 48;
						break;
					}
				}


				if (isdigit(song[c + 2]))
				{ // check for proper two digit procedure

					numBeat = numBeat * 10;

					int numBeat1 = song[c + 2];


					for (int k = 48; k < 57; ++k)
					{
						if (k == numBeat1)
						{
							numBeat1 = k - 48;
							break;
						}
					}

					numBeat = numBeat + numBeat1;

					int i = 3;
					for (; i - 3 < numBeat; ++i)
					{

						if (song[c + i] == '/') // does song have the right # of slashes for sustain
						{
							continue;
						}
						else if (song[c + i] != '/')
						{
							return false;
						}
					}
					c = c + (numBeat + 1);
				}

				else if ((song[c + 2] == '/'))
				{
					int i = 2;
					for (; i - 2 < numBeat; ++i)
					{
						if (song[c + i] == '/') // does song have the right # of slashes for sustain
						{
							continue;
						}
						else if (song[c + i] != '/')
						{
							return false;
						}
					}
					c = c + (numBeat + 1);
				}
			}
		}
	}
	return true;
}

bool prematureEnd(string song, int badBeat)
{
	for (int c = 0; c != badBeat; ++c)
		//goes through series of checks to see 
		//if entered song ends prematurely
	{
		if (isColor(song[c]))
		{

			if (isdigit(song[c + 1]))
			{// is the song following proper sustain note syntax?

				int numBeat = song[c + 1];


				for (int k = 48; k < 57; ++k)
				{
					if (k == numBeat)
					{
						numBeat = k - 48;
						break;
					}
				}


				if (isdigit(song[c + 2]))
				{ // check for proper two digit procedure

					numBeat = numBeat * 10;

					int numBeat1 = song[c + 2];


					for (int k = 48; k < 57; ++k)
					{
						if (k == numBeat1)
						{
							numBeat1 = k - 48;
							break;
						}
					}

					numBeat = numBeat + numBeat1;

					int i = 3;
					for (; i - 3 < numBeat; ++i)
					{

						if (song[c + i] == '/') // does song have the right # of slashes for sustain
						{
							continue;
						}
						else
						{
							return false;
						}
					}
					c = c + (numBeat + 1);
				}

				else if ((song[c + 2] == '/'))
				{
					int i = 2;
					for (; i - 2 < numBeat; ++i)
					{
						if (song[c + i] == '/') // does song have the right # of slashes for sustain
						{
							continue;
						}
						else if (song[c + i] != '/')
						{
							return false;
						}
					}
					c = c + (numBeat + 1);
				}
			}

			else if (song[c + 1] == '/') // is the song following normal note procedure?
			{
				++c;
				continue;
			}
			else
			{
				return false;
			}
		}
		
		else if (song[c] == '/') //is there a pause here?
		{
			continue;
		}
		else
		{
			return false;
		}

	}
	return true;
}

int badBeatFinder(string song)
{
	//goes through series of checks 
	// to see if entered song has badBeats
	int beats = 1, start = 0;
	for (int c = 0; c != song.size(); ++c)
	{

		if (isColor(song[c]))
		{

			if (isdigit(song[c + 1]))
			{// is the song following proper sustain note syntax?

				int numBeat = song[c + 1];


				for (int k = 48; k < 57; ++k)
				{
					if (k == numBeat)
					{
						numBeat = k - 48;
						break;
					}
				}


				if (isdigit(song[c + 2]))
				{ // check for proper two digit procedure

					numBeat = numBeat * 10;

					int numBeat1 = song[c + 2];


					for (int k = 48; k < 57; ++k)
					{
						if (k == numBeat1)
						{
							numBeat1 = k - 48;
							break;
						}
					}

					numBeat = numBeat + numBeat1;

					if (numBeat <= 1)
					{
						return beats;
					}

					int i = 3;
					for (; i - 3 < numBeat; ++i)
					{

						if (song[c + i] == '/') // does song have the right # of slashes for sustain
						{
							if (start == 0)
							{
								++start;
								continue;
							}
							++beats;
							continue;
						}
						else
						{
							++beats;
							return beats;
						}
					}
					c = c + (numBeat + 1);
				}

				else if (numBeat <= 1)
				{
					return beats;
				}

				else if ((song[c + 2] == '/'))
				{
					int i = 2;
					for (; i - 2 < numBeat; ++i)
					{
						if (song[c + i] == '/') // does song have the right # of slashes for sustain
						{
							if (start == 0)
							{
								++start;
								continue;
							}
							++beats;
							continue;
						}
						else
						{
							++beats;
							return beats;
						}
					}
					c = c + (numBeat + 1);
				}

				else
				{
					return beats;
				}
			}
			else if (song[c + 1] == '/') // is the song following normal note procedure?
			{
				if (start == 0)
				{
					++start;
					continue;
				}
				++beats;
				continue;
			}
			else
			{
				return beats;
			}
		}

		else if (song[c] == '/') //is there a pause here?
		{
			cout << "pause" << endl;
			if (start == 0)
			{
				++start;
				continue;
			}
			++beats;
			continue;
		}
		else
		{
			return beats;
		}
	}
	return 0;
}

string createTranslation(string song)
{
	// translates a song
	string translation = song;
	char color = 'r';
	int translationLength = 0;
	
	for (int c = 0; c != song.size(); ++c)
	{
		if (isColor(song[c]))
		{
			color = colorStore(song[c]);

			if (isdigit(song[c + 1]))
			{// is the song following proper sustain note syntax?

				int numBeat = song[c + 1];
				color = toupper(color);

				for (int k = 48; k < 57; ++k)
				{
					if (k == numBeat)
					{
						numBeat = k - 48;
						break;
					}
				}


				if (isdigit(song[c + 2]))
				{ // check for proper two digit procedure

					numBeat = numBeat * 10;

					int numBeat1 = song[c + 2];


					for (int k = 48; k < 57; ++k)
					{
						if (k == numBeat1)
						{
							numBeat1 = k - 48;
							break;
						}
					}

					numBeat = numBeat + numBeat1;

					int i = 3;
					for (; i - 3 < numBeat; ++i)
					{
						if (song[c + i] == '/') // does song have the right # of slashes for sustain
						{
							translation[(c + (i - 3)) - (translationLength)] = color;
							++translationLength;
						}
					}
					c = c + (numBeat + 1);
				}

				else if ((song[c + 2] == '/'))
				{
					int i = 2;
					for (; i - 2 < numBeat; ++i)
					{
						if (song[c + i] == '/') // does song have the right # of slashes for sustain
						{
							translation[(c + (i - 2))- (translationLength)] = color;
						}
					}
					translationLength += numBeat;
					c = c + (numBeat + 1);
				}
			}

			else if (song[c + 1] == '/') // is the song following normal note procedure?
			{
				translation[c - translationLength] = color;
				++translationLength;
				++c;
			}
		}

		else if (song[c] == '/') //is there a pause here?
		{
			translation[c - translationLength] = 'x';
			++translationLength;
		}
	}

	translation.erase(translation.find('/')); // Erases excess /'s

	return translation;
}

int translateSong(string song, string& instructions, int& badBeat)
{
	if (!hasCorrectSyntax(song))
	{
		return 1;
	}

	else if (isTranslateable(song))
	{
		instructions = createTranslation(song);
		return 0;
	}

	else if (!isTranslateable(song))
	{
		badBeat = badBeatFinder(song);
		if (!sustainDigitCheck(song, badBeat))
		{
			return 2;
		}
		if (!sustainInterruptionCheck(song, badBeat))
		{
			return 3;
		}
		if (!prematureEnd(song, badBeat))
		{
			return 4;
		}
		else
		{
			return -2;
		}
	}
	else
		return -1;
}