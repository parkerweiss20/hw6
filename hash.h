#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }

    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
       
        unsigned long long total = 0;
         std::string temp = k;
        HASH_INDEX_T str_size = k.size();
        int a_val;
        size_t arr[5];

        switch (str_size)
      {
      case 6:
          for (size_t i = 0; i < 6; i++)
          {
              a_val = letterDigitToNumber(k[i]);
              total = (total * 36) + a_val;
          }
          total = total * rValues[4];
          return total;

      default:
          if (str_size < 6)
          {
              temp.append(6 - str_size, '!');

              for (size_t i = 0; i < 6; i++)
              {
                  if (temp[i] != '!')
                  {
                      a_val = letterDigitToNumber(k[i]);
                      total = (total * 36) + a_val;
                  }
                  else
                  {
                      break;
                  }
              }
              total = total * rValues[4];
              return total;
          }
          else
          {
              unsigned long long final_total = 0;
              temp.insert(0, 30 - str_size, '!');
              std::cout << temp << std::endl;

              for (size_t i = 0; i < 5; i++)
              {
                  for (size_t j = 6 * i; j < 6 * (i + 1); j++)
                  {
                      a_val = temp[j] != '!' ? letterDigitToNumber(temp[j]) : 0;
                      total = (total * 36) + a_val;
                  }
                  arr[i] = total;
                  total = 0;
              }

              for (size_t i = 0; i < 5; i++)
              {
                  final_total += arr[i] * rValues[i];
              }

              return final_total;
          }
      }

    }

    void generateRValues()
    {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  
        
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
   
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        
        char adj_letter = tolower(letter);
        if (adj_letter <= 'z' && adj_letter >= 'a'){
            return adj_letter = adj_letter - 'a';
        }else if(adj_letter <= '9' && adj_letter >= '0'){
            return adj_letter - '0' + 26;
        }
        return 0;
    }


};
#endif
