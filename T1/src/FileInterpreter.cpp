/**
Autor: Henry Cagnini
Matrícula: 201010352
*/

#include "FileInterpreter.h"

using namespace std;

FileInterpreter::FileInterpreter() {
}

vector<SampleCollection> *FileInterpreter::readFile(char *path) {
   string *buffer = fileReader(path);
   vector<SampleCollection> *collections = sampleCollector(buffer);
   return collections;
}

vector<SampleCollection> *FileInterpreter::sampleCollector(string *buffer) {
   unsigned int last = 0, next; //intervalo onde se pega o valor
   int next_samples = 0, s_count = 0, n_smps = 0;
   double value = 1, samples[SampleCollection::max_samples];
   bool collect = true, end = false;
   vector<SampleCollection> *col = new vector<SampleCollection>();
   while(!end) {
      next = buffer->find_first_of('\n', last);
      if(next == buffer->npos) {
         next = buffer->rfind('0');
         if(next == buffer->npos || next < last) {
            throw SyntaxException();
         } else {
            next += 1;
         }
         end = true;
      }
      value = stringReader(buffer->substr(last, next-last));
      last = buffer->find_first_not_of('\n', next);
      if(collect) { //é um int que denota quantas amostras vêm pela frente
         next_samples = (int)value;
         if(s_count > 0) {
            col->push_back(new SampleCollection(samples, s_count));
            s_count = 0;
            n_smps++;
         }
         if(next_samples > SampleCollection::max_samples || next_samples < SampleCollection::min_samples) {
            if(next_samples == 0) { //chegou o zero do fim da leitura
               break;
            } else {
               throw SyntaxException();
            }
         }
         collect = false;
      } else { //é valor
         if(value >= SampleCollection::min_value && value <= SampleCollection::max_value) {
            samples[s_count] = value;
            s_count++;
            next_samples--;
            if(next_samples == 0) {
               collect = true;
            }
         } else {
            throw ValueException();
         }
      }
   }
   if(n_smps > 0 && n_smps <= max_collections) {
      return col;
   }
   delete col;
   throw SyntaxException();
}


double FileInterpreter::stringReader(string str) {
   double value, factor = 1;
   bool neg = false, over = true, first = true, err = false;
   for(string::iterator ptr = str.begin(); ptr < str.end(); ptr++) {
      if(*ptr >= '0' && *ptr <= '9') {
         if(first) {
            value = (double)(*ptr - '0');
            first = false;
         } else {
            if(over) {
               value = (value*10) + (*ptr - '0');
            } else {
               value = value + ((*ptr - '0')/(pow(10, factor)));
               factor++;
            }
         }
         continue;
      }
      if(*ptr == '.') {
         if(over && !first) {
            over = false;
            continue;
         }
      } else {
         if(*ptr == '-') {
            if(!neg && first) {
               neg = true;
               continue;
            }
         }
      }
      //if(não é nenhum dos caracteres permitidos)
      err = true;
      break;
   }
   if(err || first) {
      throw ValueException();
   }
   if(neg) {
      value *= -1;
   }
   return value;
}

string *FileInterpreter::fileReader(char *path) {
   in.open(path);
   if(in.fail()) {
      throw ReadingFileException();
   }
   int length;
   char *buffer;

   in.seekg(0, ios::end);
   length = (int)in.tellg();
   in.seekg(0, ios::beg);

   if(length < max_buffer) {
      buffer = new char [length+1];
      in.read(buffer,length);
      in.close();
      return (new string(buffer));
   }
   throw ReadingFileException();
}
