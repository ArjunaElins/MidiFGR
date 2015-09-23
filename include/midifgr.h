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

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cstdio>
#include <tclap/CmdLine.h>
#include "MidiFile.h"

/**
 * A structure to contain command line arguments
 */
struct Args {
	std::string filePath;	
};

/**
 * Get Command Line Arguments
 *
 * This function uses TCLAP library to parse command line arguments
 * 
 * @param  argc arguments count
 * @param  argv arguments vector
 * @return      parsed arguments
 */
Args getArgs(int argc, char *argv[]);

/**
 * Get finger data from user input
 * 
 * @param  note active note
 * @return      finger data
 */
char getFingerInput(char note);

/**
 * Get key string from note number
 * @param  key  note number
 * @return      key string
 */
std::string getKey(int key);

/**
 * Encode user input to finger number
 * @param  finger user input
 * @return        finger number
 */
char encode(char finger);

/**
 * Set header metadata
 * 
 * @param buffer     buffer container
 * @param trackCount number of data track
 */
void setHeader(std::vector<char> *buffer, int trackCount);

/**
 * Push finger data to buffer
 * 
 * @param buffer buffer container
 * @param data   finger data
 */
void pushToBuffer(std::vector<char> *buffer, std::vector<char> data);

/**
 * Set track metadata
 * 
 * @param trackLength track length
 */
std::vector<char> setTrackHead(int trackLength);

/**
 * Write Finger Data Buffer to File
 * 
 * @param filePath path of midi file
 * @param buffer   finger data buffer
 */
void writeFile(std::string filePath, std::vector<char> buffer);