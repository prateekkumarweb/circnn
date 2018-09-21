#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

//import a file containing entries of a matrix
//and generate a circulant version of it
vector<vector<double>> my_matrix;

void circulant_gen(string in, string out, int k)
{
    ifstream raw_matrix{ in };
     if (!raw_matrix) throw runtime_error("Can't open input file");
     ofstream output{ out };
     if (!output) throw runtime_error("Can't open output file");

     unsigned int m, n;
     raw_matrix >> m >> n;
     if(m%k != 0 || n%k != 0) throw runtime_error("invalid k");

     //get the matrix
     for (auto mm = 0; mm < m; ++mm)
     {
         vector<double> row;
         for (auto nn = 0; nn < n; ++nn)
         {
             double d;
             raw_matrix >> d;
             row.push_back(d);
         }
         my_matrix.push_back(row);

         if ((mm + 1) % k == 0)
         {
             vector<double> circulant_row;
             for (auto i = 0; i < n; i += k)
             {
                 for (auto j = 0; j < k; ++j)
                 {
                     double temp_sum{};
                     for (auto r = 0; r < k; ++r)
                     {
                         temp_sum += my_matrix[r + mm - k + 1][(r + j) % k + i];
                     }
                     circulant_row.push_back(temp_sum / k);
//                     cout << temp_sum / k << " ";
                 }
             }
             //circulant
             for (int f = 0; f < k; ++f)
             {
                 for (auto g = 0; g < circulant_row.size(); g += k)
                 {
                     for(auto p = 0; p < k; ++p)
                         output << circulant_row[(g + p + k - f) % k + g] << ' ';
                 }
                 output << '\n';
             }
         }
     }
     cout << "done" << endl;
}

int main(int argc, char **argv) {
	if (argc < 4) return -1;
	string in_addr(argv[1]);
	string out_addr(argv[2]);
	circulant_gen(in_addr, out_addr, stoi(argv[3]));
}
