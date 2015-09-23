/**
 * Arjuna: Alat Bantu Pembelajaran Piano untuk Tunanetra
 *
 * Developed by:
 * Ilham Imaduddin
 * Ahmad Shalahuddin
 * Piquitha Della Audyna
 *
 * Elektronika dan Instrumentasi
 * Universitas Gadjah Mada
 * 
 * Copyright (c) 2015 Arjuna
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 */

#include "midifgr.h"

/**
 * Main Function
 * 
 * @param  argc arguments count
 * @param  argv arguments vector
 * @return      status
 */
int main(int argc, char *argv[])
{
	Args args = getArgs(argc, argv);

	MidiFile midi(args.filePath);
	std::vector<char> buffer;

	setHeader(&buffer, midi.getTrackCount());

	for (int t = 0; t < midi.getTrackCount(); t++)
	{
		std::cout << "Track " << t + 1 << std::endl;

		std::vector<char> data;

		for (int e = 0; e < midi[t].getSize(); e++)
		{
			char note = midi[t][e][1];

			if (midi[t][e].isNoteOn())
			{
				char finger = getFingerInput(note);
				data.push_back(encode(finger));
			}
		}
		pushToBuffer(&buffer, data);
	}

	writeFile(args.filePath, buffer);

	return 0;
}

/**
 * Get Command Line Arguments
 *
 * This function uses TCLAP library to parse command line arguments
 * 
 * @param  argc arguments count
 * @param  argv arguments vector
 * @return      parsed arguments
 */
Args getArgs(int argc, char *argv[])
{
	TCLAP::CmdLine cmd("MidiFGR - Arjuna Finger Data Creator", ' ', "0.1");
	TCLAP::UnlabeledValueArg<std::string> fileArg("file", "MIDI file path", true, "", "midi path", cmd);

	cmd.parse(argc, argv);

	Args parsedArgs;
	parsedArgs.filePath = fileArg.getValue();

	return parsedArgs;
}

/**
 * Get finger data from user input
 * 
 * @param  note active note
 * @return      finger data
 */
char getFingerInput(char note)
{
	char finger;

	std::cout << getKey(note) << ": ";
	std::cin >> finger;

	return finger;
}

/**
 * Get key string from note number
 * @param  key  note number
 * @return      key string
 */
std::string getKey(int key)
{
	int octave;
	int workNote;
	std::string note;

	octave = key / 12;
	workNote = key % 12;

	switch (workNote + 1)
	{
		case 1:		note = "C";		break;
		case 2:		note = "C#";	break;
		case 3:		note = "D";		break;
		case 4:		note = "D#";	break;
		case 5:		note = "E";		break;
		case 6:		note = "F";		break;
		case 7:		note = "F#";	break;
		case 8:		note = "G";		break;
		case 9:		note = "G#";	break;
		case 10:	note = "A";		break;
		case 11:	note = "A#";	break;
		case 12:	note = "B";		break;
	}

	note.append(to_string(octave));

	return note;
}

/**
 * Encode user input to finger number
 * @param  finger user input
 * @return        finger number
 */
char encode(char finger)
{
	char code = 0;

	switch (finger)
	{
		case 'a':	code = 5; 	break;
		case 's':	code = 4; 	break;
		case 'd':	code = 3; 	break;
		case 'f':	code = 2; 	break;
		case 'g':	code = 1; 	break;
		case 'h':	code = 1; 	break;
		case 'j':	code = 2; 	break;
		case 'k':	code = 3; 	break;
		case 'l':	code = 4; 	break;
		case ';':	code = 5; 	break;
	}

	return code;
}

/**
 * Set header metadata
 * 
 * @param buffer     buffer container
 * @param trackCount number of data track
 */
void setHeader(std::vector<char> *buffer, int trackCount)
{
	buffer->push_back('M');
	buffer->push_back('T');
	buffer->push_back('f');
	buffer->push_back('g');
	buffer->push_back((char) trackCount >> 8);
	buffer->push_back((char) trackCount);
}

/**
 * Push finger data to buffer
 * 
 * @param buffer buffer container
 * @param data   finger data
 */
void pushToBuffer(std::vector<char> *buffer, std::vector<char> data)
{
	std::vector<char> head = setTrackHead(data.size());
	buffer->insert(buffer->end(), head.begin(), head.end());
	buffer->insert(buffer->end(), data.begin(), data.end());
}

/**
 * Set track metadata
 * 
 * @param trackLength track length
 */
std::vector<char> setTrackHead(int trackLength)
{
	std::vector<char> head;
	head.push_back('M');
	head.push_back('T');
	head.push_back('r');
	head.push_back('k');
	head.push_back((char) trackLength >> 24);
	head.push_back((char) trackLength >> 16);
	head.push_back((char) trackLength >> 8);
	head.push_back((char) trackLength);

	return head;
}

/**
 * Write Finger Data Buffer to File
 * 
 * @param filePath path of midi file
 * @param buffer   finger data buffer
 */
void writeFile(std::string filePath, std::vector<char> buffer)
{
	for (int i = 0; i < 4; i++)
	{
		filePath.pop_back();
	}
	filePath.append(".fgr");

	ofstream file(filePath, std::ios::out | std::ios::binary | std::ios::trunc);
	file.write(reinterpret_cast<const char*>(&buffer[0]), buffer.size());
	file.close();

	std::cout << "File saved in \"" << filePath << "\".\n";
}