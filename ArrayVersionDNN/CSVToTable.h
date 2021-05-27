#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <istream>

using namespace std;
class CSVTable {
public:
	CSVTable(const char* file_name) {
		ifstream file(file_name);
		if (file.fail()) {
			cout << "해당 경로에 위치하는 파일이 존재하지 않습니다." << endl;

		}
		else {
			while (file.good()) { //옛날 eof != 랑 똑같은듯 
				vector<string> tmp_row = csv_read_row(file);
				if (!tmp_row[0].find("#"))continue;
				else m_columns.push_back(tmp_row);
			}
			file.close();
		}
	}
	vector<vector<string>> get_table() { return m_columns; }
	~CSVTable() {

	}
private:
	vector<vector<string>> m_columns;

	inline void print_row_column() {
		for (vector<string>& tmp_row : m_columns) {
			for (string& ite : tmp_row) {
				cout << "[" << ite << "]" << "\t";
			}
			cout << endl;
		}

	}
	static vector<string> csv_read_row(istream& file) {
		stringstream result_stream;
		bool inquotes = false;
		vector<string> row;


		while (file.good()) {
			char tmp_char = file.get();
			if (!inquotes && tmp_char == '"') {
				inquotes = true;
			}
			else if (inquotes && tmp_char == '"') {
				if (file.peek() == '"') result_stream << (char)file.get();
				else inquotes = false;
			}
			else if (!inquotes && tmp_char == ',') {
				row.push_back(result_stream.str());
				result_stream.str("");
			}
			else if (!inquotes && (tmp_char == '\r' || tmp_char == '\n')) {
				if (file.peek() == '\n') file.get();
				row.push_back(result_stream.str());
				return row;
			}
			else result_stream << tmp_char;
		}
	}


};
