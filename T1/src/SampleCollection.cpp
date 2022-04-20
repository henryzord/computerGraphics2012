/**
Autor: Henry Cagnini
Matrícula: 201010352
*/

#include "SampleCollection.h"

using namespace std;

SampleCollection::SampleCollection(double samples[], int length) {
   if(length >= min_samples && length <= max_samples) {
      nsmps = 0;
      hasCDCT = false;
      hasCIDCT = false;
      int n;
      for(n = 0; n < length; n++) {
         if(samples[n] >= (double)min_value && samples[n] <= (double)max_value) {
            smps[nsmps] = samples[n];
            nsmps++;
         } else {
            break;
         }
      }
      if(n != length) {
         throw SyntaxException();
      } else { //calcula a dct
         CosinTransformer::calculateDCT(this);
         CosinTransformer::calculateIDCT(this);
         CosinTransformer::calculateCDCT(this);
         CosinTransformer::calculateCIDCT(this);
      }
   } else {
      throw SyntaxException();
   }
}

SampleCollection::SampleCollection(SampleCollection *matrix) {
   int length = matrix->getAmount();
   if(length > 0) {
      for(int n = 0; n < length; n++) {
         smps[n] = matrix->getSample(n);
         dcts[n] = matrix->getDCT(n);
         idcts[n] = matrix->getIDCT(n);
         cdcts[n] = matrix->getCDCT(n);
         cidcts[n] = matrix->getCIDCT(n);
      }
      nsmps = length;
   } else {
      throw SyntaxException();
   }
}

double SampleCollection::getSample(int index) {
   if(nsmps > 0 && index < nsmps) {
      return smps[index];
   } else {
      throw OutOfRangeException();
   }
}

double SampleCollection::getDCT(int index) {
   if(nsmps > 0 && index < nsmps) {
      return dcts[index];
   } else {
      throw OutOfRangeException();
   }
}

double SampleCollection::getIDCT(int index) {
   if(nsmps > 0 && index < nsmps) {
      return idcts[index];
   } else {
      throw OutOfRangeException();
   }
}
//
double SampleCollection::getCDCT(int index) {
   if(nsmps > 0 && index < nsmps) {
      return cdcts[index];
   } else {
      throw OutOfRangeException();
   }
}

double SampleCollection::getCIDCT(int index) {
   if(nsmps > 0 && index < nsmps) {
      return cidcts[index];
   } else {
      throw OutOfRangeException();
   }
}
//
int SampleCollection::getAmount() {
   return nsmps;
}

void SampleCollection::printSamples() {
   cout << "Sinal original:" << endl;
   if(nsmps > 0) {
      for(int n = 0; n < nsmps; n++) {
         cout << "["<< smps[n] << "]";
      }
      cout << endl << "----------" << endl;
   } else {
      cout << "Sem amostras." << endl;
   }
}

void SampleCollection::printDCT() {
   cout << "DCT:" << endl;
   if(nsmps > 0) {
      for(int n = 0; n < nsmps; n++) {
         cout << "["<< dcts[n] << "]";
      }
      cout << endl << "----------" << endl;
   } else {
      cout << "Sem amostras." << endl;
   }
}

void SampleCollection::printIDCT() {
   cout << "IDCT:" << endl;
   if(nsmps > 0) {
      for(int n = 0; n < nsmps; n++) {
         cout << "["<< idcts[n] << "]";
      }
      cout << endl << "----------" << endl;
   } else {
      cout << "Sem amostras." << endl;
   }
}

void SampleCollection::printAll() {
   printSamples();
   printDCT();
   printIDCT();
   cout << endl << "------------------------------" << endl;
}

bool SampleCollection::isCompressed() {
   if(this->hasCDCT && this->hasCIDCT) {
      return true;
   }
   return false;
}

void SampleCollection::compressCollection() {
   if(!isCompressed()) {
      CosinTransformer::calculateCDCT(this);
      CosinTransformer::calculateCIDCT(this);
   }
}

SampleCollection::~SampleCollection() {
}

/**
*Funções da CosinTransformer
*/
SampleCollection::CosinTransformer::CosinTransformer() {
}

double SampleCollection::CosinTransformer::coef(int index) {
   if(index > 0) {
      return rest_coef;
   }
   return first_coef;
}

void SampleCollection::CosinTransformer::calculateDCT(SampleCollection *matrix) {
   double sum;
   for(int f = 0; f < matrix->nsmps; f++) {
      sum = 0;
      for(int t = 0; t < matrix->nsmps; t++) {
         sum += matrix->smps[t] * cos((((2*t)+1)*(f*pi))/(2*matrix->nsmps));
      }
      matrix->dcts[f] = (double)(0.5 * coef(f) * sum);
   }
}

void SampleCollection::CosinTransformer::calculateIDCT(SampleCollection *matrix) {
   double sum;
   for(int t = 0; t < matrix->nsmps; t++) {
      sum = 0;
      for(int j = 0; j < matrix->nsmps; j++) {
         sum += coef(j) * matrix->dcts[j] * cos((((2*t)+1)*j*pi)/(2*matrix->nsmps));
      }
      matrix->idcts[t] = (double)(0.5 * sum);
   }
}

void SampleCollection::CosinTransformer::calculateCDCT(SampleCollection *matrix) {
   /*
   double sum = 0;
   int quantFactor;
   for(int n = 0; n < matrix->nsmps; n++) {
   sum += matrix->dcts[n]; //ACHAR UM QUANTFACTOR MELHOR!!
   }
   sum /= matrix->nsmps; //média dos valores
   quantFactor = ((int)sum % 25) + 2; 
   for(int n = 0; n < matrix->nsmps; n++) {
   matrix->cdcts[n] = (matrix->dcts[n])/(1 + ((1 + n) * quantFactor));
   }
   matrix->hasCDCT = true;
   */
   //int thrid = matrix->nsmps - (matrix->nsmps/3);
   int snd = matrix->nsmps/2;
   for(int n = 0; n < matrix->nsmps; n++) {
      if(n > snd) {
         matrix->cdcts[n] = 0;
      } else {
         matrix->cdcts[n] = matrix->dcts[n];
      }
   }
   matrix->hasCDCT = true;
}

void SampleCollection::CosinTransformer::calculateCIDCT(SampleCollection *matrix) {
   double sum;
   for(int t = 0; t < matrix->nsmps; t++) {
      sum = 0;
      for(int j = 0; j < matrix->nsmps; j++) {
         sum += coef(j) * matrix->cdcts[j] * cos((((2*t)+1)*j*pi)/(2*matrix->nsmps));
      }
      matrix->cidcts[t] = (double)(0.5 * sum);
   }
}