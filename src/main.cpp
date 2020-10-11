#include<iostream>
#include <list>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <iomanip>

using namespace std;

struct Simbol {
	string ime;
	string sekcija;
	int pomeraj;
	int velicina;
	char tip; // local-L, global-G
	int redniBr;
	bool definisan;
	char externglobal;
	Simbol(string ime, string sekcija, int pomeraj, int velicina, char tip, int redniBr, bool definisan, char externglob) {
		this->ime = ime;
		this->sekcija = sekcija;
		this->pomeraj = pomeraj;
		this->velicina = velicina;
		this->tip = tip;
		this->redniBr = redniBr;
		this->definisan = definisan;
		this->externglobal = externglob;
	}

};


struct Relokacija {
	int offset;
	string tip; // a-apsoluto, s-skok
	int vrednost; 
	string sekcija;
	string ime;
	bool popravi;
	Relokacija(int offset, string tip, int vrednost, string sekcija, string ime, bool popravi) {
		this->offset = offset;
		this->tip = tip;
		this->vrednost = vrednost;
		this->sekcija = sekcija;
		this->ime = ime;
		this->popravi = popravi;
	}
};

struct ObracanjeUnapred {
	string ime; 
	int path; //kod equ rez 
	int velicina; //kod equ 0, ako treba da se doda, 1 ako treba da se oduzme
	string sekcija; 
	string equsimbol; //kod equ vrednost simbola za razresavanje
	char tip; // da li je word ili byte ili equ
	ObracanjeUnapred(string ime, int path, int velicina, string sekcija, char tip, string equsimbol) {
		this->ime = ime;
		this->path = path;
		this->velicina = velicina;
		this->sekcija = sekcija;
		this->tip = tip;
		this->equsimbol = equsimbol;
	}
};

struct NerazreseniSimboli {
	string ime;
	int path; //kod equ rez 
	int velicina; //kod equ 0, ako treba da se doda, 1 ako treba da se oduzme
	string sekcija;
	string equsimbol; //kod equ vrednost simbola za razresavanje
	char tip; // da li je word ili byte ili equ
	NerazreseniSimboli(string ime, int path, int velicina, string sekcija, char tip, string equsimbol) {
		this->ime = ime;
		this->path = path;
		this->velicina = velicina;
		this->sekcija = sekcija;
		this->tip = tip;
		this->equsimbol = equsimbol;
	}
};


struct Instrukcija {
	string ime;
	int broj;
	char wordByte; //word w, byte b
	Instrukcija(string ime, int broj, char wordByte) {
		this->ime = ime;
		this->broj = broj;
		this->wordByte = wordByte;
	}
};

struct SadrzajSekcija {
	string sekcija;
	string sadrzaj;
	SadrzajSekcija(string sekcija, string sadrzaj) {
		this->sekcija = sekcija;
		this->sadrzaj = sadrzaj;
	}
};

void ispisTabeleSimbola(std::ofstream &izlazni, list<Simbol> tabelaSimbola) {
	list<Simbol>::iterator i;
	izlazni << "\n" << "Tabela simbola" << "\n";
	izlazni << '|' << std::setw(10) << "RedniBr" << '|' << std::setw(10) << "Ime" << '|' << std::setw(10) << "Sekcija" << '|' << std::setw(10) << "Pomeraj" << '|' << std::setw(10) << "Velicina" << '|' << std::setw(10) << "Tip" << '|' << "\n";
	int cnt = 0;
	
	for (i = tabelaSimbola.begin(); i != tabelaSimbola.end(); i++) {
		if (izlazni.is_open()) {
			if (i->ime.compare(i->sekcija) == 0) {
				izlazni << '|' << std::setw(10) << i->redniBr << '|' << std::setw(10) << i->ime << '|' << std::setw(10) << i->sekcija << '|' << std::setw(10) << i->pomeraj << '|' << std::setw(10) << i->velicina << '|' << std::setw(10) << i->tip << '|' << "\n";
				cnt++;
			}
			}
	}
	list<Simbol>::iterator i2;
	for (i2 = tabelaSimbola.begin(); i2 != tabelaSimbola.end(); i2++) {
		if (izlazni.is_open()) {
			if (i2->ime.compare(i2->sekcija) != 0) {
				izlazni << '|' << std::setw(10) << i2->redniBr << '|' << std::setw(10) << i2->ime << '|' << std::setw(10) << i2->sekcija << '|' << std::setw(10) << i2->pomeraj << '|' << std::setw(10) << i2->velicina << '|' << std::setw(10) << i2->tip << '|' << "\n";
				cnt++;
			}
			}
	}
}

void ispisSadrzajaSekcija(std::ofstream& izlazni, list<SadrzajSekcija> sadrzaj) {
	list<SadrzajSekcija>::iterator i;
	if (!sadrzaj.empty()) {
		izlazni << "\n" << "Sadrzaj sekcija" << "\n";
	}
	for (i = sadrzaj.begin(); i != sadrzaj.end(); i++) {
		if (izlazni.is_open()) {
			izlazni << "Sekcija:  " << i->sekcija << "\n" ;
			
					int i1 = 0;
					SadrzajSekcija sadrzajSek = *i;
					SadrzajSekcija sadrzaj1 = sadrzajSek;
					
					int k = 0;
					for (std::string::iterator it = sadrzajSek.sadrzaj.begin(); it != sadrzajSek.sadrzaj.end(); ++it) {
						if (i1 % 2 == 0 && i1 != 0) {
							
								sadrzaj1.sadrzaj.insert(i1 + k, " ");
								k++;
							
						}
						i1++;
					}

				
					izlazni <<sadrzaj1.sadrzaj << "\n";

		}
	}
}

void ispisTabelaObracanjaUnapred(std::ofstream& izlazni, list<ObracanjeUnapred> tabelaObracanjaUnapred) {
	list<ObracanjeUnapred>::iterator i;
	if (!tabelaObracanjaUnapred.empty()) {
		izlazni << "Tabela obracanja unapred" << "\n";
		izlazni << '|' << std::setw(10) << "Simbol" << '|'<< std::setw(10) << "Path" << '|'  <<  std::setw(10) << "Sekcija" << '|' << "\n";

	}
	
	for (i = tabelaObracanjaUnapred.begin(); i != tabelaObracanjaUnapred.end(); i++) {
		if (izlazni.is_open()) {
			izlazni << '|' << std::setw(10) << i->ime << '|' << std::setw(10) << i->path << '|' << std::setw(10) << i->sekcija << '|' <<  "\n";
		}
	}
}

void ispisTabelaRealokacije(std::ofstream& izlazni, list<Relokacija> tabelaRealokacija) {
	list<Relokacija>::iterator i;
	if (!tabelaRealokacija.empty()) {
		izlazni<<"\n" << "Tabela realokacija" << "\n";
	}
	string trenutnaSek;
	string prethodnaSek = "";
	for (i = tabelaRealokacija.begin(); i != tabelaRealokacija.end(); i++) {
		if (izlazni.is_open()) {

			if (prethodnaSek.compare("") == 0) {
				prethodnaSek = i->sekcija;
				trenutnaSek = i->sekcija;
				izlazni << "Rel." << i->sekcija << "\n";
				izlazni << '|' << std::setw(10) << "Offset" << '|' << std::setw(25) << "Tip" << '|' << std::setw(10) << "Vrednost" << '|' << "\n";
			}
			prethodnaSek = trenutnaSek;
			trenutnaSek = i->sekcija;
			if (prethodnaSek != trenutnaSek) {
				izlazni << "Rel." << i->sekcija << "\n";
				izlazni << '|' << std::setw(10) << "Offset" << '|' << std::setw(25) << "Tip" << '|' << std::setw(10) << "Vrednost" << '|' <<"\n";
			}
			string ss;
			ostringstream t;
			t << std::hex << i->offset;

			ss += t.str();
			izlazni << '|' << std::setw(10) << ss << '|' << std::setw(25) << i->tip << '|' << std::setw(10) << i->vrednost << '|' << "\n";
		}
	}
}

void ispisTabelaNerazresenihSimbola(std::ofstream& izlazni, list<NerazreseniSimboli> tabelaNerazresenihSimbola) {
	list<NerazreseniSimboli>::iterator i;
	if (!tabelaNerazresenihSimbola.empty()) {
		izlazni << "\n" << "Tabela nerazresenih simbola" << "\n";
	}
	for (i = tabelaNerazresenihSimbola.begin(); i != tabelaNerazresenihSimbola.end(); i++) {
		if (izlazni.is_open()) {
			izlazni << "Simbol:  " << i->ime << " " << "Trenutni rezultat: " << i->path << " Plus/Minus: " << i->velicina << " SimbolN: " << i->equsimbol << "\n";
		}
	}
}


bool postojiUTabeliSimbola(string ime, string sek, list<Simbol> tabelaSimbola) {
	list<Simbol>::iterator i;
	for (i = tabelaSimbola.begin(); i != tabelaSimbola.end(); i++) {
		if ((i->ime) == ime && (i->sekcija) == sek ) {
			return false;
		}
	}

	return true;
}

bool jeLabela(string rec) {
	string s = rec.substr(rec.size() - 1, rec.size());
	if (s.compare(":") == 0) {
		return true;
	}
	else {
		return false;
	}
}

bool jeDirektiva(string rec) {
	string rec1 = rec.substr(0, 1);
	if (rec1.compare(".") == 0)
		return true;
	else
		return false;
}

bool jeInstrukcija(string rec, list<Instrukcija> listaInstrukcija) {
	list<Instrukcija>::iterator i;
	bool postoji = false;
	for (i = listaInstrukcija.begin(); i != listaInstrukcija.end(); i++) {
		if (i->ime.compare(rec) == 0) {
			postoji = true;
			return true;
		}
	}
	if(!postoji)
		return false;
	return false;
}

string odrediAdresiranje(string rec) {
	string rec1 = rec.substr(0, 1);
	if (rec1.compare("$") == 0) { //neposredno
		//proveri da li je znak broj ili simbol
		bool hexadecimalan = false;
		string prvi_karakter = rec.substr(1, 2);
		rec = rec.substr(1, rec.size());

		if (prvi_karakter.compare("0x") == 0) {
			hexadecimalan = true;
		}


		if (rec.find_first_not_of("0123456789") != std::string::npos && !hexadecimalan) {
			//simbol
			if (rec.find_first_of(",./[]();*&^%$#@!") != std::string::npos) {
				cout << "Greska: neispravna sintaksa operanada, ne odgovora nijednom adresiranju!" << "\n";
				exit(1);
			}

			return "neposredno";
		}
		else {
			
			return "neposredno";
		}
	} // if neposredno
		
	else {
		if (rec1.compare("%") == 0) { //regdir
			rec = rec.substr(1, rec.size());
			if (rec.size() == 2) {
				string prvi = rec.substr(0, 1);
				if (prvi.compare("r") == 0) {
					string broj = rec.substr(1, 2);
					long long br = std::stoll(broj, 0, 0);
					if (br >= 0 && br <= 7) {
						return "regdir";
					}
					else {
						cout << "Greska: kod registarskog adresiranja!" << "\n";
						exit(1);
					}
				}
				else {
					cout << "Greska: kod registarskog adresiranja!" << "\n";
					exit(1);
				}
			} 
			else {
				if (rec.size() == 3) {
					string prvi = rec.substr(0, 1);
					if (prvi.compare("r") == 0) {
						string broj = rec.substr(1, 2);
						long long br = std::stoll(broj, 0, 0);
						if (br >= 0 && br <= 7) {
							string hl = rec.substr(2,3);
							if (hl.compare("h") == 0 or hl.compare("l") == 0) {
								return "regdir";
							}
							else {
								cout << "Greska: kod registarskog adresiranja!" << "\n";
								exit(1);
							}

							
						}
						else {
							cout << "Greska: kod registarskog adresiranja!" << "\n";
							exit(1);
						}
					}
					else {
						cout << "Greska: kod registarskog adresiranja!" << "\n";
						exit(1);
					}
				}
				else {


					cout << "Greska: kod registarskog adresiranja!" << "\n";
					exit(1);
				}
			}
		} //if regdir
		else {
			if (rec1.compare("(") == 0) {//regind

			
			rec = rec.substr(1, rec.size());
			string rec3 = rec.substr(0, 1);
			if (rec3.compare("%") == 0) { 
				rec = rec.substr(1, rec.size() - 2);
				if (rec.size() == 2) {
					string prvi = rec.substr(0, 1);
					if (prvi.compare("r") == 0) {
						string broj = rec.substr(1, 2);
						long long br = std::stoll(broj, 0, 0);
						if (br >= 0 && br <= 7) {
							return "regind";
						}
						else {
							cout << "Greska: kod registarskog indirektnog adresiranja!" << "\n";
							exit(1);
						}
					}
					else {
						cout << "Greska: kod registarskog indirektnog adresiranja!" << "\n";
						exit(1);
					}
				}
				else {
					cout << "Greska: kod registarskog indirektnog adresiranja!" << "\n";
					exit(1);
				}
			} 
		} //if regind
			else { //regindpom16, pcrel, memdir
				bool regindpom = false;
				bool pcrel = false;

				string word = "";
				bool zagrada = false;
				for (auto x : rec)
				{

					if (x != '(' && !zagrada)
					{
						word = word + x;
						
					}
					else
					{
						zagrada = true;
							
						}

					} //for
				if (rec.size() == word.size()) {
					//memorijsko direktno
					bool hexadecimalan = false;
					string prvi_karakter = word.substr(0, 2);


					if (prvi_karakter.compare("0x") == 0) {
						hexadecimalan = true;
					}


					if (word.find_first_not_of("0123456789") != std::string::npos && !hexadecimalan) {
						//simbol
						if (rec.find_first_of(",./[]();*&^%$#@!") != std::string::npos) {
							cout << "Greska: neispravna sintaksa operanada, ne odgovora nijednom adresiranju!" << "\n";
							exit(1);
						}

						return "memdir";
					} //if simbol
					else {
						//broj
						return "memdir";
					}//else simbol
				} //memorisjko direktno kraj

				bool hexadecimalan = false;
				string prvi_karakter = word.substr(0, 2);
				

				if (prvi_karakter.compare("0x") == 0) {
					hexadecimalan = true;
				}


				if (word.find_first_not_of("0123456789") != std::string::npos && !hexadecimalan) {
					//simbol
					rec = rec.substr(word.size(), rec.size());
					string rec2 = rec.substr(0, 1);
					if (rec2.compare("(") == 0) {//regind


						rec = rec.substr(1, rec.size());
						string rec3 = rec.substr(0, 1);
						if (rec3.compare("%") == 0) {
							rec = rec.substr(1, rec.size() - 2);
							if (rec.size() == 2) {
								if (rec.compare("pc") == 0) {
									return "pcrel";
								}
								else {
								string prvi = rec.substr(0, 1);
								if (prvi.compare("r") == 0) {
									string broj = rec.substr(1, 2);
									long long br = std::stoll(broj, 0, 0);
									if (br >= 0 && br <= 6) {
										return "regindpom";

									}
									else {
										if (br == 7) {
											return "pcrel";

										}
										else {
											cout << "Greska: kod registarskog indirektnog adresiranja!" << "\n";
											exit(1);
										}
									}
								}
								else {
									cout << "Greska: kod registarskog indirektnog adresiranja!" << "\n";
									exit(1);
								}
							}//else pc relativno
							}
							else {
								cout << "Greska: kod registarskog indirektnog adresiranja!" << "\n";
								exit(1);
							}
						}
					} //if regindpom
					
				} //if simbol
				else {
					//broj		
					rec = rec.substr(word.size() , rec.size());
					string rec2 = rec.substr(0, 1);
					if (rec2.compare("(") == 0) {//regind


						rec = rec.substr(1, rec.size());
						string rec3 = rec.substr(0, 1);
						if (rec3.compare("%") == 0) {
							rec = rec.substr(1, rec.size() - 2);
							if (rec.size() == 2) {
								
								string prvi = rec.substr(0, 1);
								if (prvi.compare("r") == 0) {
									string broj = rec.substr(1, 2);
									long long br = std::stoll(broj, 0, 0);
									if (br >= 0 && br <= 7) {
										return "regindpom";
									}
										else {
											cout << "Greska: kod registarskog indirektnog adresiranja!" << "\n";
											exit(1);
										}
									
								}
								else {
									cout << "Greska: kod registarskog indirektnog adresiranja!" << "\n";
									exit(1);
								}
							
						}
							else {
								cout << "Greska: kod registarskog indirektnog adresiranja!" << "\n";
								exit(1);
							}
						}
					} //if regindpom
					
				}//else simbol
				

			} //else regind

		} //else regdir

	} //else neposredno
	cout << "Greska: neispravna sintaksa operanada, ne odgovora nijednom adresiranju!" << "\n";
	exit(1);
		
}

string odrediAdresiranjeJump(string rec) {

	string prvi = rec.substr(0, 1);
	if (prvi.compare("*") == 0) {
		rec = rec.substr(1, rec.size());

	string rec1 = rec.substr(0, 1);

		if (rec1.compare("%") == 0) { //regdir
			rec = rec.substr(1, rec.size());
			if (rec.size() == 2) {
				string prvi = rec.substr(0, 1);
				if (prvi.compare("r") == 0) {
					string broj = rec.substr(1, 2);
					long long br = std::stoll(broj, 0, 0);
					if (br >= 0 && br <= 7) {
						return "regdir";
					}
					else {
						cout << "Greska: kod registarskog adresiranja!" << "\n";
						exit(1);
					}
				}
				else {
					cout << "Greska: kod registarskog adresiranja!" << "\n";
					exit(1);
				}
			}
			else {
				if (rec.size() == 3) {
					string prvi = rec.substr(0, 1);
					if (prvi.compare("r") == 0) {
						string broj = rec.substr(1, 2);
						long long br = std::stoll(broj, 0, 0);
						if (br >= 0 && br <= 7) {
							string hl = rec.substr(2, 3);
							if (hl.compare("h") == 0 or hl.compare("l") == 0) {
								return "regdir";
							}
							else {
								cout << "Greska: kod registarskog adresiranja!" << "\n";
								exit(1);
							}


						}
						else {
							cout << "Greska: kod registarskog adresiranja!" << "\n";
							exit(1);
						}
					}
					else {
						cout << "Greska: kod registarskog adresiranja!" << "\n";
						exit(1);
					}
				}
				else {


					cout << "Greska: kod registarskog adresiranja!" << "\n";
					exit(1);
				}
			}
		} //if regdir
		else {
			if (rec1.compare("(") == 0) {//regind


				rec = rec.substr(1, rec.size());
				string rec3 = rec.substr(0, 1);
				if (rec3.compare("%") == 0) {
					rec = rec.substr(1, rec.size() - 2);
					if (rec.size() == 2) {
						string prvi = rec.substr(0, 1);
						if (prvi.compare("r") == 0) {
							string broj = rec.substr(1, 2);
							long long br = std::stoll(broj, 0, 0);
							if (br >= 0 && br <= 7) {
								return "regind";
							}
							else {
								cout << "Greska: kod registarskog indirektnog adresiranja!" << "\n";
								exit(1);
							}
						}
						else {
							cout << "Greska: kod registarskog indirektnog adresiranja!" << "\n";
							exit(1);
						}
					}
					else {
						cout << "Greska: kod registarskog indirektnog adresiranja!" << "\n";
						exit(1);
					}
				}
			} //if regind
			else { //regindpom16, pcrel, memdir
				bool regindpom = false;
				bool pcrel = false;

				string word = "";
				bool zagrada = false;
				for (auto x : rec)
				{

					if (x != '(' && !zagrada)
					{
						word = word + x;

					}
					else
					{
						zagrada = true;

					}

				} //for
				if (rec.size() == word.size()) {
					//memorijsko direktno
					bool hexadecimalan = false;
					string prvi_karakter = word.substr(0, 2);


					if (prvi_karakter.compare("0x") == 0) {
						hexadecimalan = true;
					}


					if (word.find_first_not_of("0123456789") != std::string::npos && !hexadecimalan) {
						//simbol
						if (rec.find_first_of(",./[]();*&^%$#@!") != std::string::npos) {
							cout << "Greska: neispravna sintaksa operanada, ne odgovora nijednom adresiranju!" << "\n";
							exit(1);
						}

						return "memdir";
					} //if simbol
					else {
						//broj
						return "memdir";
					}//else simbol
				} //memorisjko direktno kraj

				bool hexadecimalan = false;
				string prvi_karakter = word.substr(0, 2);


				if (prvi_karakter.compare("0x") == 0) {
					hexadecimalan = true;
				}


				if (word.find_first_not_of("0123456789") != std::string::npos && !hexadecimalan) {
					//simbol
					rec = rec.substr(word.size(), rec.size());
					string rec2 = rec.substr(0, 1);
					if (rec2.compare("(") == 0) {//regind


						rec = rec.substr(1, rec.size());
						string rec3 = rec.substr(0, 1);
						if (rec3.compare("%") == 0) {
							rec = rec.substr(1, rec.size() - 2);
							if (rec.size() == 2) {
								if (rec.compare("pc") == 0) {
									return "pcrel";
								}
								else {
									string prvi = rec.substr(0, 1);
									if (prvi.compare("r") == 0) {
										string broj = rec.substr(1, 2);
										long long br = std::stoll(broj, 0, 0);
										if (br >= 0 && br <= 6) {
											return "regindpom";

										}
										else {
											if (br == 7) {
												return "pcrel";

											}
											else {
												cout << "Greska: kod registarskog indirektnog adresiranja!" << "\n";
												exit(1);
											}
										}
									}
									else {
										cout << "Greska: kod registarskog indirektnog adresiranja!" << "\n";
										exit(1);
									}
								}//else pc relativno
							}
							else {
								cout << "Greska: kod registarskog indirektnog adresiranja!" << "\n";
								exit(1);
							}
						}
					} //if regindpom

				} //if simbol
				else {
					//broj		
					rec = rec.substr(word.size(), rec.size());
					string rec2 = rec.substr(0, 1);
					if (rec2.compare("(") == 0) {//regind


						rec = rec.substr(1, rec.size());
						string rec3 = rec.substr(0, 1);
						if (rec3.compare("%") == 0) {
							rec = rec.substr(1, rec.size() - 2);
							if (rec.size() == 2) {

								string prvi = rec.substr(0, 1);
								if (prvi.compare("r") == 0) {
									string broj = rec.substr(1, 2);
									long long br = std::stoll(broj, 0, 0);
									if (br >= 0 && br <= 7) {
										return "regindpom";
									}
									else {
										cout << "Greska: kod registarskog indirektnog adresiranja!" << "\n";
										exit(1);
									}

								}
								else {
									cout << "Greska: kod registarskog indirektnog adresiranja!" << "\n";
									exit(1);
								}

							}
							else {
								cout << "Greska: kod registarskog indirektnog adresiranja!" << "\n";
								exit(1);
							}
						}
					} //if regindpom

				}//else simbol


			} //else regind

		} //else regdir
	cout << "Greska: neispravna sintaksa operanada, ne odgovora nijednom adresiranju!" << "\n";
	exit(1);
		}
		else {
		
	//proveri da li je znak broj ili simbol
			bool hexadecimalan = false;
			string prvi_karakter = rec.substr(0, 2);
			rec = rec.substr(1, rec.size());

			if (prvi_karakter.compare("0x") == 0) {
				hexadecimalan = true;
			}


			if (rec.find_first_not_of("0123456789") != std::string::npos && !hexadecimalan) {
				//simbol
				if (rec.find_first_of(",./[]();*&^%$#@!") != std::string::npos) {
					cout << "Greska: neispravna sintaksa operanada, ne odgovora nijednom adresiranju!" << "\n";
					exit(1);
				}

				return "neposredno";
			}
			else {

				return "neposredno";
			}


}

}

void neposrednoAdresiranje(string sim, string trenutnaSekcija, int locationCounter, int & brojacRbr, list<ObracanjeUnapred>& tabelaObracanjaUnapred, list<Simbol>& tabelaSimbola, list<Relokacija>& tabelaRealokacije, list<SadrzajSekcija>& listaSadrzajaSekcija) {
	string rec1 = sim.substr(0, 1);

	//proveri da li je znak broj ili simbol
	bool hexadecimalan = false;
	string prvi_karakter = sim.substr(1, 2);
	sim = sim.substr(1, sim.size());

	if (prvi_karakter.compare("0x") == 0) {
		hexadecimalan = true;
	}


	if (sim.find_first_not_of("0123456789") != std::string::npos && !hexadecimalan) {
		//simbol

		list<Simbol>::iterator i;
		bool postojiuTabeli = false;
		for (i = tabelaSimbola.begin(); i != tabelaSimbola.end(); i++) {
			if ((i->ime).compare(sim) == 0) {
				//ako vec postoji u tabeli simbola
				if (i->definisan) {
					//definisan
					if ((i->tip) == 'L') {
						//ako je local
						//OK
						list<Simbol>::iterator i1;
						for (i1 = tabelaSimbola.begin(); i1 != tabelaSimbola.end(); i1++) {
							if ((i1->sekcija).compare(i->sekcija) == 0 && (i1->ime).compare(i->sekcija) == 0) {
								Relokacija rel = Relokacija(locationCounter, " R_386_32", i1->redniBr, trenutnaSekcija, sim, false);
								tabelaRealokacije.push_back(rel);

								unsigned char b1 = i->pomeraj & 255;
								unsigned char b2 = (i->pomeraj >> 8) & 255;
								if (i->pomeraj < -32768 || i->pomeraj > 32767) {
									cout << "Greska:  literal nije odgovarajuce sirine kod neposrednog adresiranja!" << "\n";
									exit(1);
								}

								string ss;
								ostringstream t;
								t << std::hex << (int)b1;
								/*		if (dodajNulu) {
											ss = "0";
										} */
								string prvi;
								prvi = t.str();
								if (prvi.size() == 1) {
									ss = "0";
								}
								ss += t.str();
								string drugi;
								ostringstream t1;
								t1 << std::hex << (int)b2;
								drugi = t1.str();
								if (drugi.size() == 1) {
									ss += "0";
								}
								ss += t1.str();


								list<SadrzajSekcija>::iterator i2;
								for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


									if ((i2->sekcija).compare(trenutnaSekcija) == 0) {

										i2->sadrzaj += ss;

									}
								}



							}//if postoji sekcija
						}//for sekcija
					}//if local
					else { //ako je global
						//OK
						int redniBr = i->redniBr;
						Relokacija rel = Relokacija(locationCounter, " R_386_32", i->redniBr, trenutnaSekcija, "", false);
						tabelaRealokacije.push_back(rel);

						list<SadrzajSekcija>::iterator i2;
						for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


							if ((i2->sekcija).compare(trenutnaSekcija) == 0) {

								i2->sadrzaj += "0000";

							}
						}
					}

				} //if definisan
				else {
					//postoji u tabeli ali nije definisan tabela obracanja unapred

					if ((i->tip) == 'L') {
						//dodaj novu bool vrednost u tabelu simbola da oznaci da treba da uradi i->pomeraj & 255; a ne samo da upise pomeraj
						//greska
						ObracanjeUnapred obracanjeUna = ObracanjeUnapred(sim, locationCounter, 2, trenutnaSekcija, 'w', "");
						tabelaObracanjaUnapred.push_back(obracanjeUna);

						list<Simbol>::iterator i1;
						for (i1 = tabelaSimbola.begin(); i1 != tabelaSimbola.end(); i1++) {
							if ((i1->ime).compare(i->ime) == 0) {
								Relokacija rel = Relokacija(locationCounter, " R_386_32", i1->redniBr, trenutnaSekcija, sim, true);
								tabelaRealokacije.push_back(rel);


								list<SadrzajSekcija>::iterator i2;
								for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


									if ((i2->sekcija).compare(trenutnaSekcija) == 0) {

										i2->sadrzaj += "0000";

									}
								}


							}//if postoji sekcija
						}//for sekcija

					}
					else {
						//ako je global sve isto, ne dodajem u tabeli obracanja unapred
						//ovo je OK
						int redniBr = i->redniBr;
						Relokacija rel = Relokacija(locationCounter, " R_386_32", i->redniBr, trenutnaSekcija, "", false);
						tabelaRealokacije.push_back(rel);


						list<SadrzajSekcija>::iterator i2;
						for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


							if ((i2->sekcija).compare(trenutnaSekcija) == 0) {

								i2->sadrzaj += "0000";

							}
						}
					}

				} //else definisan
				postojiuTabeli = true;
			} // if da li postoji u tabeli simbola

		} //for

		if (!postojiuTabeli) {
			//ne postoji u tabeli, dodati i tabela obracanja unapred
			Simbol s = Simbol(sim, trenutnaSekcija, 0, NULL, 'L', brojacRbr, false, ' ');
			tabelaSimbola.push_back(s);
			brojacRbr++;

			ObracanjeUnapred obracanjeUna = ObracanjeUnapred(sim, locationCounter, 2, trenutnaSekcija, 'w', "");
			tabelaObracanjaUnapred.push_back(obracanjeUna);

			list<Simbol>::iterator i1;
			for (i1 = tabelaSimbola.begin(); i1 != tabelaSimbola.end(); i1++) {
				if ((i1->ime).compare(sim) == 0) {
					Relokacija rel = Relokacija(locationCounter, " R_386_32", i1->redniBr, trenutnaSekcija, sim, true);
					tabelaRealokacije.push_back(rel);

					list<SadrzajSekcija>::iterator i3;
					for (i3 = listaSadrzajaSekcija.begin(); i3 != listaSadrzajaSekcija.end(); i3++) {


						if ((i3->sekcija).compare(trenutnaSekcija) == 0) {

							i3->sadrzaj += "0000";

						}
					}


				}//if postoji sekcija
			}//for sekcija


		}
	}
	else {
		//broj

		long long n = std::stoll(sim, 0, 0);

		unsigned char b1 = n & 255;
		unsigned char b2 = (n >> 8) & 255;
		if (n < -32768 || n > 32767) {
			cout << "Greska:  literal nije odgovarajuce sirine kod neposrednog adresiranja!" << "\n";
			exit(1);
		}

		string ss;
		ostringstream t;
		t << std::hex << (int)b1;
		/*		if (dodajNulu) {
					ss = "0";
				} */
		string prvi;
		prvi = t.str();
		if (prvi.size() == 1) {
			ss = "0";
		}
		ss += t.str();
		string drugi;
		ostringstream t1;
		t1 << std::hex << (int)b2;
		drugi = t1.str();
		if (drugi.size() == 1) {
			ss += "0";
		}
		ss += t1.str();


		list<SadrzajSekcija>::iterator i2;
		for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {
			//	cout << i2->sekcija << "\n";

			if ((i2->sekcija).compare(trenutnaSekcija) == 0) {
				//		cout << i2->sekcija<< " 1" <<  "\n";
				i2->sadrzaj += ss;

			}
		}

	}//else broj
	

}

void memorijskoAdresiranje(string sim, string trenutnaSekcija, int locationCounter, int& brojacRbr, list<ObracanjeUnapred>& tabelaObracanjaUnapred, list<Simbol>& tabelaSimbola, list<Relokacija>& tabelaRealokacije, list<SadrzajSekcija>& listaSadrzajaSekcija) {
	//proveri da li je znak broj ili simbol
	bool hexadecimalan = false;
	string prvi_karakter = sim.substr(0, 2);


	if (prvi_karakter.compare("0x") == 0) {
		hexadecimalan = true;
	}


	if (sim.find_first_not_of("0123456789") != std::string::npos && !hexadecimalan) {
		//simbol

		list<Simbol>::iterator i;
		bool postojiuTabeli = false;
		for (i = tabelaSimbola.begin(); i != tabelaSimbola.end(); i++) {
			if ((i->ime).compare(sim) == 0) {
				//ako vec postoji u tabeli simbola
				if (i->definisan) {
					//definisan
					if ((i->tip) == 'L') {
						//ako je local
						//OK
						list<Simbol>::iterator i1;
						for (i1 = tabelaSimbola.begin(); i1 != tabelaSimbola.end(); i1++) {
							if ((i1->sekcija).compare(i->sekcija) == 0 && (i1->ime).compare(i->sekcija) == 0) {
								Relokacija rel = Relokacija(locationCounter, " R_386_32", i1->redniBr, trenutnaSekcija, sim, false);
								tabelaRealokacije.push_back(rel);

								unsigned char b1 = i->pomeraj & 255;
								unsigned char b2 = (i->pomeraj >> 8) & 255;
								if (i->pomeraj < -32768 || i->pomeraj > 32767) {
									cout << "Greska:  literal nije odgovarajuce sirine kod neposrednog adresiranja!" << "\n";
									exit(1);
								}

								string ss;
								ostringstream t;
								t << std::hex << (int)b1;
								/*		if (dodajNulu) {
											ss = "0";
										} */
								string prvi;
								prvi = t.str();
								if (prvi.size() == 1) {
									ss = "0";
								}
								ss += t.str();
								string drugi;
								ostringstream t1;
								t1 << std::hex << (int)b2;
								drugi = t1.str();
								if (drugi.size() == 1) {
									ss += "0";
								}
								ss += t1.str();


								list<SadrzajSekcija>::iterator i2;
								for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


									if ((i2->sekcija).compare(trenutnaSekcija) == 0) {

										i2->sadrzaj += ss;

									}
								}



							}//if postoji sekcija
						}//for sekcija
					}//if local
					else { //ako je global
						//OK
						int redniBr = i->redniBr;
						Relokacija rel = Relokacija(locationCounter, " R_386_32", i->redniBr, trenutnaSekcija, "", false);
						tabelaRealokacije.push_back(rel);

						list<SadrzajSekcija>::iterator i2;
						for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


							if ((i2->sekcija).compare(trenutnaSekcija) == 0) {

								i2->sadrzaj += "0000";

							}
						}
					}

				} //if definisan
				else {
					//postoji u tabeli ali nije definisan tabela obracanja unapred

					if ((i->tip) == 'L') {
						//dodaj novu bool vrednost u tabelu simbola da oznaci da treba da uradi i->pomeraj & 255; a ne samo da upise pomeraj
						//greska
						ObracanjeUnapred obracanjeUna = ObracanjeUnapred(sim, locationCounter, 2, trenutnaSekcija, 'w', "");
						tabelaObracanjaUnapred.push_back(obracanjeUna);

						list<Simbol>::iterator i1;
						for (i1 = tabelaSimbola.begin(); i1 != tabelaSimbola.end(); i1++) {
							if ((i1->ime).compare(i->ime) == 0) {
								Relokacija rel = Relokacija(locationCounter, " R_386_32", i1->redniBr, trenutnaSekcija, sim, true);
								tabelaRealokacije.push_back(rel);


								list<SadrzajSekcija>::iterator i2;
								for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


									if ((i2->sekcija).compare(trenutnaSekcija) == 0) {

										i2->sadrzaj += "0000";

									}
								}


							}//if postoji sekcija
						}//for sekcija

					}
					else {
						//ako je global sve isto, ne dodajem u tabeli obracanja unapred
						//ovo je OK
						int redniBr = i->redniBr;
						Relokacija rel = Relokacija(locationCounter, " R_386_32", i->redniBr, trenutnaSekcija, "", false);
						tabelaRealokacije.push_back(rel);


						list<SadrzajSekcija>::iterator i2;
						for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


							if ((i2->sekcija).compare(trenutnaSekcija) == 0) {

								i2->sadrzaj += "0000";

							}
						}
					}

				} //else definisan
				postojiuTabeli = true;
			} // if da li postoji u tabeli simbola

		} //for

		if (!postojiuTabeli) {
			//ne postoji u tabeli, dodati i tabela obracanja unapred
			Simbol s = Simbol(sim, trenutnaSekcija, 0, NULL, 'L', brojacRbr, false, ' ');
			tabelaSimbola.push_back(s);
			brojacRbr++;

			ObracanjeUnapred obracanjeUna = ObracanjeUnapred(sim, locationCounter, 2, trenutnaSekcija, 'w', "");
			tabelaObracanjaUnapred.push_back(obracanjeUna);

			list<Simbol>::iterator i1;
			for (i1 = tabelaSimbola.begin(); i1 != tabelaSimbola.end(); i1++) {
				if ((i1->ime).compare(sim) == 0) {
					Relokacija rel = Relokacija(locationCounter, " R_386_32", i1->redniBr, trenutnaSekcija, sim, true);
					tabelaRealokacije.push_back(rel);

					list<SadrzajSekcija>::iterator i3;
					for (i3 = listaSadrzajaSekcija.begin(); i3 != listaSadrzajaSekcija.end(); i3++) {


						if ((i3->sekcija).compare(trenutnaSekcija) == 0) {

							i3->sadrzaj += "0000";

						}
					}


				}//if postoji sekcija
			}//for sekcija


		}
	}
	else {
		//broj

		long long n = std::stoll(sim, 0, 0);

		unsigned char b1 = n & 255;
		unsigned char b2 = (n >> 8) & 255;
		if (n < -32768 || n > 32767) {
			cout << "Greska:  literal nije odgovarajuce sirine kod neposrednog adresiranja!" << "\n";
			exit(1);
		}

		string ss;
		ostringstream t;
		t << std::hex << (int)b1;
		/*		if (dodajNulu) {
					ss = "0";
				} */
		string prvi;
		prvi = t.str();
		if (prvi.size() == 1) {
			ss = "0";
		}
		ss += t.str();
		string drugi;
		ostringstream t1;
		t1 << std::hex << (int)b2;
		drugi = t1.str();
		if (drugi.size() == 1) {
			ss += "0";
		}
		ss += t1.str();


		list<SadrzajSekcija>::iterator i2;
		for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {
			//	cout << i2->sekcija << "\n";

			if ((i2->sekcija).compare(trenutnaSekcija) == 0) {
				//		cout << i2->sekcija<< " 1" <<  "\n";
				i2->sadrzaj += ss;

			}
		}

	}//else broj


}

void pcrelativnoAdresiranje(string sim, string trenutnaSekcija, int locationCounter, int& brojacRbr, list<ObracanjeUnapred>& tabelaObracanjaUnapred, list<Simbol>& tabelaSimbola, list<Relokacija>& tabelaRealokacije, list<SadrzajSekcija>& listaSadrzajaSekcija) {
	//proveri da li je znak broj ili simbol
	


	if (sim.find_first_not_of("0123456789") != std::string::npos) {
		//simbol

		list<Simbol>::iterator i;
		bool postojiuTabeli = false;
		for (i = tabelaSimbola.begin(); i != tabelaSimbola.end(); i++) {
			if ((i->ime).compare(sim) == 0) {
				//ako vec postoji u tabeli simbola
				if (i->definisan) {
					//definisan
					if ((i->tip) == 'L') {
						//ako je local
						//OK
						list<Simbol>::iterator i1;
						for (i1 = tabelaSimbola.begin(); i1 != tabelaSimbola.end(); i1++) {
							if ((i1->sekcija).compare(i->sekcija) == 0 && (i1->ime).compare(i->sekcija) == 0) {
								Relokacija rel = Relokacija(locationCounter, " R_386_PC32", i1->redniBr, trenutnaSekcija, sim, false);
								tabelaRealokacije.push_back(rel);

								int pom = i->pomeraj - 2;

								unsigned char b1 = pom & 255;
								unsigned char b2 = (pom >> 8) & 255;
								if (pom < -32768 || pom > 32767) {
									cout << "Greska:  literal nije odgovarajuce sirine kod neposrednog adresiranja!" << "\n";
									exit(1);
								}

								string ss;
								ostringstream t;
								t << std::hex << (int)b1;
								/*		if (dodajNulu) {
											ss = "0";
										} */
								string prvi;
								prvi = t.str();
								if (prvi.size() == 1) {
									ss = "0";
								}
								ss += t.str();
								string drugi;
								ostringstream t1;
								t1 << std::hex << (int)b2;
								drugi = t1.str();
								if (drugi.size() == 1) {
									ss += "0";
								}
								ss += t1.str();


								list<SadrzajSekcija>::iterator i2;
								for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


									if ((i2->sekcija).compare(trenutnaSekcija) == 0) {

										i2->sadrzaj += ss;

									}
								}



							}//if postoji sekcija
						}//for sekcija
					}//if local
					else { //ako je global
						//OK
						int redniBr = i->redniBr;
						Relokacija rel = Relokacija(locationCounter, " R_386_PC32", i->redniBr, trenutnaSekcija, "", false);
						tabelaRealokacije.push_back(rel);

						int pom = 0 - 2;

						unsigned char b1 = pom & 255;
						unsigned char b2 = (pom >> 8) & 255;
						if (pom < -32768 || pom > 32767) {
							cout << "Greska:  literal nije odgovarajuce sirine kod neposrednog adresiranja!" << "\n";
							exit(1);
						}

						string ss;
						ostringstream t;
						t << std::hex << (int)b1;
						/*		if (dodajNulu) {
									ss = "0";
								} */
						string prvi;
						prvi = t.str();
						if (prvi.size() == 1) {
							ss = "0";
						}
						ss += t.str();
						string drugi;
						ostringstream t1;
						t1 << std::hex << (int)b2;
						drugi = t1.str();
						if (drugi.size() == 1) {
							ss += "0";
						}
						ss += t1.str();

						list<SadrzajSekcija>::iterator i2;
						for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


							if ((i2->sekcija).compare(trenutnaSekcija) == 0) {

								i2->sadrzaj += ss;

							}
						}
					}

				} //if definisan
				else {
					//postoji u tabeli ali nije definisan tabela obracanja unapred

					if ((i->tip) == 'L') {
						//dodaj novu bool vrednost u tabelu simbola da oznaci da treba da uradi i->pomeraj & 255; a ne samo da upise pomeraj
						//greska
						ObracanjeUnapred obracanjeUna = ObracanjeUnapred(sim, locationCounter, 2, trenutnaSekcija, 'r', "");
						tabelaObracanjaUnapred.push_back(obracanjeUna);

						list<Simbol>::iterator i1;
						for (i1 = tabelaSimbola.begin(); i1 != tabelaSimbola.end(); i1++) {
							if ((i1->ime).compare(i->ime) == 0) {
								Relokacija rel = Relokacija(locationCounter, " R_386_PC32", i1->redniBr, trenutnaSekcija, sim, true);
								tabelaRealokacije.push_back(rel);


								list<SadrzajSekcija>::iterator i2;
								for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


									if ((i2->sekcija).compare(trenutnaSekcija) == 0) {

										i2->sadrzaj += "0000";

									}
								}


							}//if postoji sekcija
						}//for sekcija

					}
					else {
						//ako je global sve isto, ne dodajem u tabeli obracanja unapred
						//ovo je OK
						int redniBr = i->redniBr;
						Relokacija rel = Relokacija(locationCounter, " R_386_PC32", i->redniBr, trenutnaSekcija, "", false);
						tabelaRealokacije.push_back(rel);

						int pom = 0 - 2;

						unsigned char b1 = pom & 255;
						unsigned char b2 = (pom >> 8) & 255;
						if (pom < -32768 || pom > 32767) {
							cout << "Greska:  literal nije odgovarajuce sirine kod neposrednog adresiranja!" << "\n";
							exit(1);
						}

						string ss;
						ostringstream t;
						t << std::hex << (int)b1;
						/*		if (dodajNulu) {
									ss = "0";
								} */
						string prvi;
						prvi = t.str();
						if (prvi.size() == 1) {
							ss = "0";
						}
						ss += t.str();
						string drugi;
						ostringstream t1;
						t1 << std::hex << (int)b2;
						drugi = t1.str();
						if (drugi.size() == 1) {
							ss += "0";
						}
						ss += t1.str();

						list<SadrzajSekcija>::iterator i2;
						for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


							if ((i2->sekcija).compare(trenutnaSekcija) == 0) {

								i2->sadrzaj += ss;

							}
						}
					}

				} //else definisan
				postojiuTabeli = true;
			} // if da li postoji u tabeli simbola

		} //for

		if (!postojiuTabeli) {
			//ne postoji u tabeli, dodati i tabela obracanja unapred
			Simbol s = Simbol(sim, trenutnaSekcija, 0, NULL, 'L', brojacRbr, false, ' ');
			tabelaSimbola.push_back(s);
			brojacRbr++;

			ObracanjeUnapred obracanjeUna = ObracanjeUnapred(sim, locationCounter, 2, trenutnaSekcija, 'r', "");
			tabelaObracanjaUnapred.push_back(obracanjeUna);

			list<Simbol>::iterator i1;
			for (i1 = tabelaSimbola.begin(); i1 != tabelaSimbola.end(); i1++) {
				if ((i1->ime).compare(sim) == 0) {
					Relokacija rel = Relokacija(locationCounter, " R_386_PC32", i1->redniBr, trenutnaSekcija, sim, true);
					tabelaRealokacije.push_back(rel);

					list<SadrzajSekcija>::iterator i3;
					for (i3 = listaSadrzajaSekcija.begin(); i3 != listaSadrzajaSekcija.end(); i3++) {


						if ((i3->sekcija).compare(trenutnaSekcija) == 0) {

							i3->sadrzaj += "0000";

						}
					}


				}//if postoji sekcija
			}//for sekcija


		}
	}
	


}

void obradaDirGlobal(list<Simbol> tabelaSimbola) {
	list<Simbol>::iterator i;
	bool greska = false;
	for (i = tabelaSimbola.begin(); i != tabelaSimbola.end(); i++) {
		if ( (i->sekcija.compare("UND") == 0) && i->externglobal == 'G') {
			//greska
			cout <<  "Greska: simbol " << i->ime << " je global, ali nije definisan u fajlu!" << "\n";
			greska = true;
		}
	}
	if (greska)
		exit(1);
}

void obradaDirExtern(list<Simbol> tabelaSimbola) {
	list<Simbol>::iterator i;
	bool greska = false;
	for (i = tabelaSimbola.begin(); i != tabelaSimbola.end(); i++) {
		if ((i->sekcija.compare("UND") != 0) && i->externglobal == 'E') {
			//greska
			cout << "Greska: simbol " << i->ime << " je extern, on ne treba da bude definisan u fajlu!" << "\n";
			greska = true;
		}
	}
	if (greska)
		exit(1);
}

void razresavanjeTabeleObracanja(list<Simbol> tabelaSimbola, list<ObracanjeUnapred> tabelaObracanjaUnapred, list<SadrzajSekcija> listaSadrzajaSekcija) {

	list<ObracanjeUnapred>::iterator i;
	for (i = tabelaObracanjaUnapred.begin(); i != tabelaObracanjaUnapred.end(); i++) {
		if (i->tip == 'b') {
			//sredi byte
			list<SadrzajSekcija>::iterator i2;
			for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


				if ((i2->sekcija).compare(i->sekcija) == 0) {
					int i1 = 0;
					SadrzajSekcija sadrzajSek = *i2;
					for (std::string::iterator it = sadrzajSek.sadrzaj.begin(); it != sadrzajSek.sadrzaj.end(); ++it) {
						if (i1 % 2 == 0) {
						//	cout << i->path << " " << i1 / 2 << "\n";
							if (i1 / 2 == i->path) {
						//		cout << "Ok " << i2->sadrzaj  << "\n";

								i2->sadrzaj.replace(i1, 2*i->velicina, "11"); //4 = 2*broj baajtova koje treba izmeniti
						//		cout << "Ok1 " << i2->sadrzaj << "\n";
							}

						}
						i1++;
					} //for

				}
			}//for
		} // if b
		else {
			if (i->tip == 'w') {

			}
			else {
				if (i->tip == 'e') {

				} //if tip  = e
			}// else tip = w
		} // else tip = b
	}

	//kako tokom razresavanja labele da se izmeni sadrzaj
	/*
	list<SadrzajSekcija>::iterator i2;
	for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


		if ((i2->sekcija).compare(trenutnaSekcija) == 0) {
			int i1 = 0;
			SadrzajSekcija sadrzajSek = *i2;
			for (std::string::iterator it = sadrzajSek.sadrzaj.begin(); it != sadrzajSek.sadrzaj.end(); ++it) {
				if (i1 % 2 == 0) {
					if (i1 / 2 == 2) {
						i2->sadrzaj.replace(i1, 4, "1111"); //4 = 2*broj baajtova koje treba izmeniti
					}

				}
				i1++;
			}

		}
	}
	*/
}

list<Instrukcija> popuniListuInstrukcija() {
	list<Instrukcija> listaInstrukcija;
	Instrukcija instr = Instrukcija("halt", 0, 'w');
	listaInstrukcija.push_back(instr);
	Instrukcija instr1 = Instrukcija("haltb", 0, 'b');
	listaInstrukcija.push_back(instr1);

	Instrukcija instr2 = Instrukcija("iret", 1, 'w');
	listaInstrukcija.push_back(instr2);
	Instrukcija instr3 = Instrukcija("iretb", 1, 'b');
	listaInstrukcija.push_back(instr3);

	Instrukcija instr4 = Instrukcija("ret", 2, 'w');
	listaInstrukcija.push_back(instr4);
	Instrukcija instr5= Instrukcija("retb",2, 'b');
	listaInstrukcija.push_back(instr5);

	Instrukcija instr6 = Instrukcija("int", 3, 'w');
	listaInstrukcija.push_back(instr6);
	Instrukcija instr7 = Instrukcija("intb", 3, 'b');
	listaInstrukcija.push_back(instr7);

	Instrukcija instr8 = Instrukcija("call", 4, 'w');
	listaInstrukcija.push_back(instr8);
	Instrukcija instr9 = Instrukcija("callb", 4, 'b');
	listaInstrukcija.push_back(instr9);

	Instrukcija instr10 = Instrukcija("jmp", 5, 'w');
	listaInstrukcija.push_back(instr10);
	Instrukcija instr11 = Instrukcija("jmpb", 5, 'b');
	listaInstrukcija.push_back(instr11);

	Instrukcija instr12 = Instrukcija("jeq", 6, 'w');
	listaInstrukcija.push_back(instr12);
	Instrukcija instr13 = Instrukcija("jeqb", 6, 'b');
	listaInstrukcija.push_back(instr13);

	Instrukcija instr14 = Instrukcija("jne", 7, 'w');
	listaInstrukcija.push_back(instr14);
	Instrukcija instr15 = Instrukcija("jneb", 7, 'b');
	listaInstrukcija.push_back(instr15);

	Instrukcija instr16 = Instrukcija("jgt", 8, 'w');
	listaInstrukcija.push_back(instr16);
	Instrukcija instr17 = Instrukcija("jgtb", 8, 'b');
	listaInstrukcija.push_back(instr17);

	Instrukcija instr18 = Instrukcija("push", 9, 'w');
	listaInstrukcija.push_back(instr18);
	Instrukcija instr19 = Instrukcija("pushb", 9, 'b');
	listaInstrukcija.push_back(instr19);

	Instrukcija instr20 = Instrukcija("pop", 10, 'w');
	listaInstrukcija.push_back(instr20);
	Instrukcija instr21 = Instrukcija("popb", 10, 'b');
	listaInstrukcija.push_back(instr21);

	Instrukcija instr22 = Instrukcija("xchg", 11, 'w');
	listaInstrukcija.push_back(instr22);
	Instrukcija instr23 = Instrukcija("xchgb", 11, 'b');
	listaInstrukcija.push_back(instr23);

	Instrukcija instr24 = Instrukcija("mov", 12, 'w');
	listaInstrukcija.push_back(instr24);
	Instrukcija instr25 = Instrukcija("movb", 12, 'b');
	listaInstrukcija.push_back(instr25);

	Instrukcija instr26 = Instrukcija("add", 13, 'w');
	listaInstrukcija.push_back(instr26);
	Instrukcija instr27 = Instrukcija("addb", 13, 'b');
	listaInstrukcija.push_back(instr27);

	Instrukcija instr28 = Instrukcija("sub", 14, 'w');
	listaInstrukcija.push_back(instr28);
	Instrukcija instr29 = Instrukcija("subb", 14, 'b');
	listaInstrukcija.push_back(instr29);

	Instrukcija instr30 = Instrukcija("mul", 15, 'w');
	listaInstrukcija.push_back(instr30);
	Instrukcija instr31 = Instrukcija("mulb", 15, 'b');
	listaInstrukcija.push_back(instr31);

	Instrukcija instr32 = Instrukcija("div", 16, 'w');
	listaInstrukcija.push_back(instr32);
	Instrukcija instr33 = Instrukcija("divb", 16, 'b');
	listaInstrukcija.push_back(instr33);

	Instrukcija instr34 = Instrukcija("cmp", 17, 'w');
	listaInstrukcija.push_back(instr34);
	Instrukcija instr35 = Instrukcija("cmpb", 17, 'b');
	listaInstrukcija.push_back(instr35);

	Instrukcija instr36 = Instrukcija("not", 18, 'w');
	listaInstrukcija.push_back(instr36);
	Instrukcija instr37 = Instrukcija("notb", 18, 'b');
	listaInstrukcija.push_back(instr37);

	Instrukcija instr38 = Instrukcija("and", 19, 'w');
	listaInstrukcija.push_back(instr38);
	Instrukcija instr39 = Instrukcija("andb", 19, 'b');
	listaInstrukcija.push_back(instr39);

	Instrukcija instr40 = Instrukcija("or", 20, 'w');
	listaInstrukcija.push_back(instr40);
	Instrukcija instr41 = Instrukcija("orb", 20, 'b');
	listaInstrukcija.push_back(instr41);

	Instrukcija instr42 = Instrukcija("xor", 21, 'w');
	listaInstrukcija.push_back(instr42);
	Instrukcija instr43 = Instrukcija("xorb", 21, 'b');
	listaInstrukcija.push_back(instr43);

	Instrukcija instr44 = Instrukcija("test", 22, 'w');
	listaInstrukcija.push_back(instr44);
	Instrukcija instr45 = Instrukcija("testb", 22, 'b');
	listaInstrukcija.push_back(instr45);

	Instrukcija instr46 = Instrukcija("shl", 23, 'w');
	listaInstrukcija.push_back(instr46);
	Instrukcija instr47 = Instrukcija("shlb", 23, 'b');
	listaInstrukcija.push_back(instr47);

	Instrukcija instr48 = Instrukcija("shr", 24, 'w');
	listaInstrukcija.push_back(instr48);
	Instrukcija instr49 = Instrukcija("shrb", 24, 'b');
	listaInstrukcija.push_back(instr49);
//	cout << listaInstrukcija.size() << "\n";
	return listaInstrukcija;
}

int main(int argc, char* argv[]) {
	list<Simbol> tabelaSimbola;
	list<Relokacija> tabelaRealokacije;

	list<NerazreseniSimboli> tabelaNerazresenihSimbola;

	list<ObracanjeUnapred> tabelaObracanjaUnapred;

	list<Instrukcija> listaInstrukcija;

	list<SadrzajSekcija> listaSadrzajaSekcija;

	string sadrzajSekcije;

	


	int brojacRbr = 1;
	int locationCounter = 0;
	ifstream ulaz("test.txt");
	ofstream izlaz("izlazTest.txt");
	/*
	ifstream ulaz;
	ofstream izlaz;
	ulaz.open(argv[1]);


	izlaz.open(argv[2]);

	*/

	Simbol s = Simbol("UND", "UND", NULL, 0, 'L', 0, " ", ' ');

	tabelaSimbola.push_back(s);

	listaInstrukcija = popuniListuInstrukcija();

	string line;

	string trenutnaSekcija = "UND";

	bool alignDirective = false;
	int alignSim;
	

	while (std::getline(ulaz, line)) {
		if(!line.empty()) {

		//stavljam sve reci iz linije u listu
		list<string> reci;
		
		string word = "";
		bool belina = false;

		for (auto x : line)
		{
		
			if (x != ' ')
			{
				word = word + x;
				belina = true;
			}
			else
			{
				if (belina == true) {
					reci.push_back(word);
					word = "";
					belina = false;
				}
				
			}

		} // for
		if(word.compare("") != 0)
		reci.push_back(word);


		string tok;
		
		list<string> reci1;
		reci1 = reci;

		//uklanjanje zareza sa pocetka reci
		string tok1;
		while (!reci1.empty()) {
			tok1 = reci.front();
			reci1.erase(reci1.begin());
			reci.erase(reci.begin());
			string zarez = tok1.substr(0, 1);
			if (zarez.compare(",") == 0) {
				tok1 = tok1.substr(1, tok1.size()-1);
				
			}
			reci.push_back(tok1);

		}
		list<string> reci2;
		reci2 = reci;

		//uklanjanje zareza sa kraja reci
		string tok2;
		while (!reci2.empty()) {
			tok2 = reci.front();
			reci2.erase(reci2.begin());
			reci.erase(reci.begin());
			int last = tok2.size();
			string zarez1 = tok2.substr(last-1, last);
			if (zarez1.compare(",") == 0) {
				tok2 = tok2.substr(0, last-1);

			}
			reci.push_back(tok2);

		}

		
		if (!reci.empty()) {

			tok = reci.front();
			reci.erase(reci.begin());
			
		}


	/*	while (!reci.empty()) {
			tok = reci.front();
			reci.erase(reci.begin());
			cout << tok<< "\n";

					} 
			*/
		bool lab1 = false;

		if (jeLabela(tok)) {
			string s = tok.substr(0, tok.size() - 1);
			
			list<Simbol>::iterator i;
			bool postoji = false;
			for (i = tabelaSimbola.begin(); i != tabelaSimbola.end(); i++) {
				if ((i->ime) == s && !(i->definisan)) {
					postoji = true;
					i->pomeraj = locationCounter;
					i->definisan = true;
					i->sekcija = trenutnaSekcija;
					if (i->tip == 'L') {
						list<Simbol>::iterator i1;
						int redniBr;
						for (i1 = tabelaSimbola.begin(); i1 != tabelaSimbola.end(); i1++) {
							if ((i1->ime).compare(i->sekcija) == 0 && (i1->sekcija).compare(i->sekcija) == 0) {
								redniBr = i1->redniBr;
							}//if redniBroj
						}//for sekciju
						list<Relokacija>::iterator i2;

						for (i2 = tabelaRealokacije.begin(); i2 != tabelaRealokacije.end(); i2++) {
							if (i2->vrednost == i->redniBr) {
								i2->vrednost = redniBr;
								i2->popravi = false;
							} //if rBr za promenu
						}//for realokacija
					}//if L
				}
			}
			if (!postoji) {
				Simbol s1 = Simbol(s, trenutnaSekcija, locationCounter, NULL, 'L', brojacRbr, true, ' ');

				tabelaSimbola.push_back(s1);
				brojacRbr++;
			}
			if (!reci.empty()) {
				tok = reci.front(); 
				reci.erase(reci.begin());
			}
			lab1 = true;
		}
			
			if (jeDirektiva(tok)) {
				if (tok.compare(".global") == 0) {
					while (!reci.empty()) {
						string sim = reci.front();
						reci.erase(reci.begin());
						//dodaj u tabelu simbola, sekcija "UND", tip 'G', pomeraj 0, velicina null, definisan false, ime sim to sto smo dohvatili
						Simbol s = Simbol(sim, "UND", 0, NULL, 'G', brojacRbr, false, 'G');

						tabelaSimbola.push_back(s);
						brojacRbr++;
					} //while
					
				} //if global
				else {
					if (tok.compare(".extern") == 0) {
						while (!reci.empty()) {
							string sim = reci.front();
							reci.erase(reci.begin());
							//dodaj u tabelu simbola, sekcija "UND", tip 'G', pomeraj 0, velicina null, definisan false, ime sim to sto smo dohvatili
							Simbol s = Simbol(sim, "UND", 0, NULL, 'G', brojacRbr, false, 'E');

							tabelaSimbola.push_back(s);
							brojacRbr++;
						} //while

					} // if exter
					else {
						if (tok.compare(".text") == 0) {
							
							Simbol s = Simbol("text", "text", NULL, 0, 'L', brojacRbr, true, ' ');

							tabelaSimbola.push_back(s);
							brojacRbr++;

							if (trenutnaSekcija.compare("UND") != 0) {
								list<Simbol>::iterator i;
								for (i = tabelaSimbola.begin(); i != tabelaSimbola.end(); i++) {
									if ((i->ime).compare(trenutnaSekcija) == 0) {
										i->velicina = locationCounter;
										locationCounter = 0;
									}
								}
							}

							trenutnaSekcija = "text";
						}
						else {
							if (tok.compare(".data") == 0) {
								Simbol s = Simbol("data", "data", NULL, 0, 'L', brojacRbr, true, ' ');

								tabelaSimbola.push_back(s);
								brojacRbr++;


								if (trenutnaSekcija.compare("UND") != 0) {
									list<Simbol>::iterator i;
									for (i = tabelaSimbola.begin(); i != tabelaSimbola.end(); i++) {
										if ((i->ime).compare(trenutnaSekcija) == 0) {
											i->velicina = locationCounter;
											locationCounter = 0;
										}
									}
								}
								trenutnaSekcija = "data";
							}
							else {
								if (tok.compare(".bss") == 0) {
									Simbol s = Simbol("bss", "bss", NULL, 0, 'L', brojacRbr, true, ' ');

									tabelaSimbola.push_back(s);
									brojacRbr++;

									if (trenutnaSekcija.compare("UND") != 0) {
										list<Simbol>::iterator i;
										for (i = tabelaSimbola.begin(); i != tabelaSimbola.end(); i++) {
											if ((i->ime).compare(trenutnaSekcija) == 0) {
												i->velicina = locationCounter;
												locationCounter = 0;
											}
										}
									}
									trenutnaSekcija = "bss";
								}
								else {
									if (tok.compare(".rodata") == 0) {
										
										Simbol s = Simbol("rodata", "rodata", NULL, 0, 'L', brojacRbr, true, ' ');

										tabelaSimbola.push_back(s);
										brojacRbr++;

										if (trenutnaSekcija.compare("UND") != 0) {
											list<Simbol>::iterator i;
											for (i = tabelaSimbola.begin(); i != tabelaSimbola.end(); i++) {
												if ((i->ime).compare(trenutnaSekcija) == 0) {
													i->velicina = locationCounter;
													locationCounter = 0;
												}
											}
										}
										trenutnaSekcija = "rodata";
									}
									else {
										if (tok.compare(".section") == 0) {
											string sim = reci.front();
											reci.erase(reci.begin());

											if (!reci.empty()) {
												cout<< "Greska: .section treba da ima samo jedno ime sekcije!" << "\n";
												exit(1);
											}

											Simbol s = Simbol(sim, sim, NULL, 0, 'L', brojacRbr, true, ' ');

											tabelaSimbola.push_back(s);
											brojacRbr++;

											if (trenutnaSekcija.compare("UND") != 0) {
												list<Simbol>::iterator i;
												for (i = tabelaSimbola.begin(); i != tabelaSimbola.end(); i++) {
													if ((i->ime).compare(trenutnaSekcija) == 0) {
														i->velicina = locationCounter;
														locationCounter = 0;
													}
												}
											}

											trenutnaSekcija = sim;


										} 
										else {
											if (tok.compare(".skip") == 0) {
											
													string sim = reci.front();
													reci.erase(reci.begin());

													if (!reci.empty()) {
														cout << "Greska: .skip treba da ima samo jedan literal!" << "\n";
														exit(1);
													}

													if (sim.find_first_not_of("0123456789") != std::string::npos) {
														cout << "Greska: .skip treba da ima samo jedan literal koji je tipa int!" << "\n";
														exit(1);
													}

													int sim1;

													sim1 = stoi(sim); // sim je int
													

													locationCounter += sim1;

											/*		while (sim1 > 0) {
														sim1 = sim1 - 1;
														sadrzajSekcije += "00";

													} 

													*/
													
													bool postojiSekcija = false;
													if (!listaSadrzajaSekcija.empty()) {
														
														list<SadrzajSekcija>::iterator i2;
														for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


															if ((i2->sekcija).compare(trenutnaSekcija) == 0) {
																postojiSekcija = true;
																
															}
														}

														if (!postojiSekcija) {
															SadrzajSekcija s = SadrzajSekcija(trenutnaSekcija, "");
															listaSadrzajaSekcija.push_back(s);
														}
													}
													else {
														SadrzajSekcija s = SadrzajSekcija(trenutnaSekcija, "");
														listaSadrzajaSekcija.push_back(s);
														
													}

													sim1 = stoi(sim);

													while (sim1 > 0) {
														sim1 = sim1 - 1;
														
														list<SadrzajSekcija>::iterator i2;
														for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


															if ((i2->sekcija).compare(trenutnaSekcija) == 0) {
																i2->sadrzaj += "00";

															}
														}


														
													}
													

													//kako tokom razresavanja labele da se izmeni sadrzaj
													/*
													list<SadrzajSekcija>::iterator i2;
													for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


														if ((i2->sekcija).compare(trenutnaSekcija) == 0) {
															int i1 = 0;
															SadrzajSekcija sadrzajSek = *i2;
															for (std::string::iterator it = sadrzajSek.sadrzaj.begin(); it != sadrzajSek.sadrzaj.end(); ++it) {
																if (i1 % 2 == 0) {
																	if (i1 / 2 == 2) {
																		i2->sadrzaj.replace(i1, 4, "1111"); //4 = 2*broj baajtova koje treba izmeniti
																	}

																}
																i1++;
															}

														}
													}
													*/
													
													//kako tokom razresavanja labele da se izmeni sadrzaj
													/*
													int i1 = 0;
													for (std::string::iterator it = sadrzajSekcije.begin(); it != sadrzajSekcije.end(); ++it) {
														if (i1 % 2 == 0) {
															if (i1/2 == 2) {
																sadrzajSekcije.replace(i1, 4, "1111"); //4 = 2*broj baajtova koje treba izmeniti
															}
														
														}
														i1++;
													}
													*/

											}// if skip
											else {
											if (tok.compare(".byte") == 0) {
												while (!reci.empty()) {
													string sim = reci.front();
													reci.erase(reci.begin());

													string minus = sim.substr(0, 1);
													string prvi_karakter;
													if (minus.compare("-") != 0) {
														prvi_karakter = sim.substr(0, 2);
													}
													else {
														prvi_karakter = sim.substr(1, 2);
													}

													bool hexadecimalan = false;
													if (prvi_karakter.compare("0x") == 0) {
														hexadecimalan = true;
													}


													if (sim.find_first_not_of("0123456789") != std::string::npos && !hexadecimalan && minus.compare("-") != 0) {
														//ako je simbol
														
															list<Simbol>::iterator i;
															bool postojiuTabeli = false;
															for (i = tabelaSimbola.begin(); i != tabelaSimbola.end(); i++) {
																if (i->ime.compare(sim) == 0) {
																	//ako vec postoji u tabeli simbola
																	if (i->definisan) {
																		//definisan
																		if ((i->tip) == 'L') {
																			//ako je local
																			list<Simbol>::iterator i1;
																			for (i1 = tabelaSimbola.begin(); i1 != tabelaSimbola.end(); i1++) {
																				if ((i1->sekcija).compare(i->sekcija) == 0 && (i1->ime).compare(i->sekcija) == 0) {
																					Relokacija rel = Relokacija(locationCounter, " R_386_32", i1->redniBr, trenutnaSekcija, sim, false);
																					tabelaRealokacije.push_back(rel);

																				//	bool dodajNulu = false;
																				//	if (i->pomeraj <= 15) {
																				//		dodajNulu = true;
																				//	}
																					
																					unsigned char b1 = i->pomeraj & 255;
																					if (i->pomeraj < -128 || i->pomeraj > 127) {
																						cout << "Greska: u direktivi .byte literal nije odgovarajuce sirine!" << "\n";
																						exit(1);
																					}

																					string ss;
																					ostringstream t;
																					t << std::hex << (int)b1;
																				/*	if (dodajNulu) {
																						ss = "0";
																					} */
																					string prvi;
																					prvi = t.str();
																					if (prvi.size() == 1) {
																						ss = "0";
																					}

																					ss += t.str();

																					bool postojiSekcija = false;
																					if (!listaSadrzajaSekcija.empty()) {

																						list<SadrzajSekcija>::iterator i2;
																						for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


																							if ((i2->sekcija).compare(trenutnaSekcija) == 0) {
																								postojiSekcija = true;

																							}
																						}

																						if (!postojiSekcija) {
																							SadrzajSekcija s = SadrzajSekcija(trenutnaSekcija, "");
																							listaSadrzajaSekcija.push_back(s);
																						}
																					}
																					else {
																						SadrzajSekcija s = SadrzajSekcija(trenutnaSekcija, "");
																						listaSadrzajaSekcija.push_back(s);

																					}




																					list<SadrzajSekcija>::iterator i2;
																					for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


																						if ((i2->sekcija).compare(trenutnaSekcija) == 0) {

																							i2->sadrzaj += ss;

																						}
																					}



																				}//if postoji sekcija
																			}//for sekcija
																		}//if local
																		else { //ako je global
																			int redniBr = i->redniBr;
																			Relokacija rel = Relokacija(locationCounter, " R_386_32", i->redniBr, trenutnaSekcija, "", false);
																			tabelaRealokacije.push_back(rel);


																			bool postojiSekcija = false;
																			if (!listaSadrzajaSekcija.empty()) {

																				list<SadrzajSekcija>::iterator i2;
																				for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


																					if ((i2->sekcija).compare(trenutnaSekcija) == 0) {
																						postojiSekcija = true;

																					}
																				}

																				if (!postojiSekcija) {
																					SadrzajSekcija s = SadrzajSekcija(trenutnaSekcija, "");
																					listaSadrzajaSekcija.push_back(s);
																				}
																			}
																			else {
																				SadrzajSekcija s = SadrzajSekcija(trenutnaSekcija, "");
																				listaSadrzajaSekcija.push_back(s);

																			}

																			list<SadrzajSekcija>::iterator i2;
																			for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


																				if ((i2->sekcija).compare(trenutnaSekcija) == 0) {

																					i2->sadrzaj += "00";

																				}
																			}
																		}

																	} //if definisan
																	else {
																		//postoji u tabeli ali nije definisan tabela obracanja unapred
																		if ((i->tip) == 'L') {
																			//dodaj novu bool vrednost u tabelu simbola da oznaci da treba da uradi i->pomeraj & 255; a ne samo da upise pomeraj
																			
																			ObracanjeUnapred obracanjeUna = ObracanjeUnapred(sim, locationCounter, 1, trenutnaSekcija, 'b', "");
																			tabelaObracanjaUnapred.push_back(obracanjeUna);

																			list<Simbol>::iterator i1;
																			for (i1 = tabelaSimbola.begin(); i1 != tabelaSimbola.end(); i1++) {
																				if ((i1->ime).compare(i->ime) == 0) {
																					Relokacija rel = Relokacija(locationCounter, " R_386_32", i1->redniBr, trenutnaSekcija, sim, true);
																					tabelaRealokacije.push_back(rel);

																					bool postojiSekcija = false;
																					if (!listaSadrzajaSekcija.empty()) {

																						list<SadrzajSekcija>::iterator i2;
																						for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


																							if ((i2->sekcija).compare(trenutnaSekcija) == 0) {
																								postojiSekcija = true;

																							}
																						}

																						if (!postojiSekcija) {
																							SadrzajSekcija s = SadrzajSekcija(trenutnaSekcija, "");
																							listaSadrzajaSekcija.push_back(s);
																						}
																					}
																					else {
																						SadrzajSekcija s = SadrzajSekcija(trenutnaSekcija, "");
																						listaSadrzajaSekcija.push_back(s);

																					}

																					list<SadrzajSekcija>::iterator i2;
																					for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


																						if ((i2->sekcija).compare(trenutnaSekcija) == 0) {

																							i2->sadrzaj += "00";

																						}
																					}


																				}//if postoji sekcija
																			}//for sekcija

																		}
																		else {
																			//ako je global sve isto, ne dodajem u tabeli obracanja unapred
																			int redniBr = i->redniBr;
																			Relokacija rel = Relokacija(locationCounter, " R_386_32", i->redniBr, trenutnaSekcija, "", false);
																			tabelaRealokacije.push_back(rel);

																			bool postojiSekcija = false;
																			if (!listaSadrzajaSekcija.empty()) {

																				list<SadrzajSekcija>::iterator i2;
																				for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


																					if ((i2->sekcija).compare(trenutnaSekcija) == 0) {
																						postojiSekcija = true;

																					}
																				}

																				if (!postojiSekcija) {
																					SadrzajSekcija s = SadrzajSekcija(trenutnaSekcija, "");
																					listaSadrzajaSekcija.push_back(s);
																				}
																			}
																			else {
																				SadrzajSekcija s = SadrzajSekcija(trenutnaSekcija, "");
																				listaSadrzajaSekcija.push_back(s);

																			}


																			list<SadrzajSekcija>::iterator i2;
																			for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


																				if ((i2->sekcija).compare(trenutnaSekcija) == 0) {

																					i2->sadrzaj += "00";

																				}
																			}
																		}

																	} //else definisan
																	postojiuTabeli = true;
																} // if da li postoji u tabeli simbola

															} //for

															if (!postojiuTabeli) {
																//ne postoji u tabeli, dodati i tabela obracanja unapred
																Simbol s = Simbol(sim, trenutnaSekcija, 0, NULL, 'L', brojacRbr, false, ' ');
																tabelaSimbola.push_back(s);
																brojacRbr++;

																ObracanjeUnapred obracanjeUna = ObracanjeUnapred(sim, locationCounter, 1, trenutnaSekcija, 'b', "");
																tabelaObracanjaUnapred.push_back(obracanjeUna);

																list<Simbol>::iterator i1;
																for (i1 = tabelaSimbola.begin(); i1 != tabelaSimbola.end(); i1++) {
																	if ((i1->ime).compare(sim) == 0) {
																		Relokacija rel = Relokacija(locationCounter, " R_386_32", i1->redniBr, trenutnaSekcija, sim, true);
																		tabelaRealokacije.push_back(rel);


																		bool postojiSekcija = false;
																		if (!listaSadrzajaSekcija.empty()) {

																			list<SadrzajSekcija>::iterator i2;
																			for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


																				if ((i2->sekcija).compare(trenutnaSekcija) == 0) {
																					postojiSekcija = true;

																				}
																			}

																			if (!postojiSekcija) {
																				SadrzajSekcija s = SadrzajSekcija(trenutnaSekcija, "");
																				listaSadrzajaSekcija.push_back(s);
																			}
																		}
																		else {
																			SadrzajSekcija s = SadrzajSekcija(trenutnaSekcija, "");
																			listaSadrzajaSekcija.push_back(s);

																		}



																		list<SadrzajSekcija>::iterator i3;
																		for (i3 = listaSadrzajaSekcija.begin(); i3 != listaSadrzajaSekcija.end(); i3++) {


																			if ((i3->sekcija).compare(trenutnaSekcija) == 0) {

																				i3->sadrzaj += "00";

																			}
																		}


																	}//if postoji sekcija
																}//for sekcija


															}
														
															locationCounter += 1;
													}
													else { 
														//ako je broj
														long long n = std::stoll(sim, 0, 0);
													/*	bool dodajNulu = false;
														if (n <= 15 && n>=0) {
															dodajNulu = true;
														} */
														
														unsigned char b1 = n & 255;
														if (n < -128 ||n > 127) {
															cout << "Greska: u direktivi .byte literal nije odgovarajuce sirine!" << "\n";
															exit(1);
														}

														string ss;          
														ostringstream t;  
														t << std::hex << (int)b1;
														
													/*	if (dodajNulu) {
															ss = "0";
														} */
														string prvi;
														prvi = t.str();
														if (prvi.size() == 1) {
															ss = "0";
														}
														ss += t.str();

														bool postojiSekcija = false;
														if (!listaSadrzajaSekcija.empty()) {

															list<SadrzajSekcija>::iterator i2;
															for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


																if ((i2->sekcija).compare(trenutnaSekcija) == 0) {
																	postojiSekcija = true;

																}
															}

															if (!postojiSekcija) {
																SadrzajSekcija s = SadrzajSekcija(trenutnaSekcija, "");
																listaSadrzajaSekcija.push_back(s);
															}
														}
														else {
															SadrzajSekcija s = SadrzajSekcija(trenutnaSekcija, "");
															listaSadrzajaSekcija.push_back(s);

														}

														list<SadrzajSekcija>::iterator i2;
														for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {
														//	cout << i2->sekcija << "\n";

															if ((i2->sekcija).compare(trenutnaSekcija) == 0) {
														//		cout << i2->sekcija<< " 1" <<  "\n";
																i2->sadrzaj += ss;

															}
														}

														locationCounter += 1;

													}


											

												} //while
												} //	if byte
												else {
												if (tok.compare(".word") == 0) {
													while (!reci.empty()) {
														string sim = reci.front();
														reci.erase(reci.begin());
														string minus = sim.substr(0, 1);
														string prvi_karakter;
														if (minus.compare("-") != 0) {
															prvi_karakter = sim.substr(0, 2);
														}
														else {
															prvi_karakter = sim.substr(1, 2);
														}

														bool hexadecimalan = false;
														

														if (prvi_karakter.compare("0x") == 0) {
															hexadecimalan = true;
														}

														


														if (sim.find_first_not_of("0123456789") != std::string::npos && !hexadecimalan && minus.compare("-") != 0) {
															//ako je simbol

															list<Simbol>::iterator i;
															bool postojiuTabeli = false;
															for (i = tabelaSimbola.begin(); i != tabelaSimbola.end(); i++) {
																if ((i->ime).compare(sim) == 0) {
																	//ako vec postoji u tabeli simbola
																	if (i->definisan) {
																		//definisan
																		if ((i->tip) == 'L') {
																			//ako je local
																			//OK
																			list<Simbol>::iterator i1;
																			for (i1 = tabelaSimbola.begin(); i1 != tabelaSimbola.end(); i1++) {
																				if ((i1->sekcija).compare(i->sekcija) == 0 && (i1->ime).compare(i->sekcija) == 0) {
																					
																						Relokacija rel = Relokacija(locationCounter, " R_386_32", i1->redniBr, trenutnaSekcija, sim, false);
																						tabelaRealokacije.push_back(rel);
																					

																					unsigned char b1 = i->pomeraj & 255;
																					unsigned char b2 = (i->pomeraj >> 8) & 255;
																					if (i->pomeraj < -32768 || i->pomeraj > 32767) {
																						cout << "Greska: u direktivi .word literal nije odgovarajuce sirine!" << "\n";
																						exit(1);
																					}

																					string ss;
																					ostringstream t;
																					t << std::hex << (int)b1;
																					/*		if (dodajNulu) {
																								ss = "0";
																							} */
																					string prvi;
																					prvi = t.str();
																					if (prvi.size() == 1) {
																						ss = "0";
																					}
																					ss += t.str();
																					string drugi;
																					ostringstream t1;
																					t1 << std::hex << (int)b2;
																					drugi = t1.str();
																					if (drugi.size() == 1) {
																						ss += "0";
																					}
																					ss += t1.str();

																					bool postojiSekcija = false;
																					if (!listaSadrzajaSekcija.empty()) {

																						list<SadrzajSekcija>::iterator i2;
																						for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


																							if ((i2->sekcija).compare(trenutnaSekcija) == 0) {
																								postojiSekcija = true;

																							}
																						}

																						if (!postojiSekcija) {
																							SadrzajSekcija s = SadrzajSekcija(trenutnaSekcija, "");
																							listaSadrzajaSekcija.push_back(s);
																						}
																					}
																					else {
																						SadrzajSekcija s = SadrzajSekcija(trenutnaSekcija, "");
																						listaSadrzajaSekcija.push_back(s);

																					}




																					list<SadrzajSekcija>::iterator i2;
																					for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


																						if ((i2->sekcija).compare(trenutnaSekcija) == 0) {

																							i2->sadrzaj += ss;

																						}
																					}



																				}//if postoji sekcija
																			}//for sekcija
																		}//if local
																		else { //ako je global
																			//OK
																			int redniBr = i->redniBr;
																			Relokacija rel = Relokacija(locationCounter, " R_386_32", i->redniBr, trenutnaSekcija, "", false);
																			tabelaRealokacije.push_back(rel);


																			bool postojiSekcija = false;
																			if (!listaSadrzajaSekcija.empty()) {

																				list<SadrzajSekcija>::iterator i2;
																				for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


																					if ((i2->sekcija).compare(trenutnaSekcija) == 0) {
																						postojiSekcija = true;

																					}
																				}

																				if (!postojiSekcija) {
																					SadrzajSekcija s = SadrzajSekcija(trenutnaSekcija, "");
																					listaSadrzajaSekcija.push_back(s);
																				}
																			}
																			else {
																				SadrzajSekcija s = SadrzajSekcija(trenutnaSekcija, "");
																				listaSadrzajaSekcija.push_back(s);

																			}

																			list<SadrzajSekcija>::iterator i2;
																			for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


																				if ((i2->sekcija).compare(trenutnaSekcija) == 0) {

																					i2->sadrzaj += "0000";

																				}
																			}
																		}

																	} //if definisan
																	else {
																		//postoji u tabeli ali nije definisan tabela obracanja unapred
																		
																		if ((i->tip) == 'L') {
																			//dodaj novu bool vrednost u tabelu simbola da oznaci da treba da uradi i->pomeraj & 255; a ne samo da upise pomeraj
																			//greska
																			ObracanjeUnapred obracanjeUna = ObracanjeUnapred(sim, locationCounter, 2, trenutnaSekcija, 'w', "");
																			tabelaObracanjaUnapred.push_back(obracanjeUna);

																			list<Simbol>::iterator i1;
																			for (i1 = tabelaSimbola.begin(); i1 != tabelaSimbola.end(); i1++) {
																				if ( (i1->ime).compare(i->ime) == 0) {
																					Relokacija rel = Relokacija(locationCounter, " R_386_32", i1->redniBr, trenutnaSekcija, sim, true);
																					tabelaRealokacije.push_back(rel);

																					bool postojiSekcija = false;
																					if (!listaSadrzajaSekcija.empty()) {

																						list<SadrzajSekcija>::iterator i2;
																						for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


																							if ((i2->sekcija).compare(trenutnaSekcija) == 0) {
																								postojiSekcija = true;

																							}
																						}

																						if (!postojiSekcija) {
																							SadrzajSekcija s = SadrzajSekcija(trenutnaSekcija, "");
																							listaSadrzajaSekcija.push_back(s);
																						}
																					}
																					else {
																						SadrzajSekcija s = SadrzajSekcija(trenutnaSekcija, "");
																						listaSadrzajaSekcija.push_back(s);

																					}

																					list<SadrzajSekcija>::iterator i2;
																					for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


																						if ((i2->sekcija).compare(trenutnaSekcija) == 0) {

																							i2->sadrzaj += "0000";

																						}
																					}


																				}//if postoji sekcija
																			}//for sekcija

																		}
																		else {
																			//ako je global sve isto, ne dodajem u tabeli obracanja unapred
																			//ovo je OK
																			int redniBr = i->redniBr;
																			Relokacija rel = Relokacija(locationCounter, " R_386_32", i->redniBr, trenutnaSekcija, "", false);
																			tabelaRealokacije.push_back(rel);

																			bool postojiSekcija = false;
																			if (!listaSadrzajaSekcija.empty()) {

																				list<SadrzajSekcija>::iterator i2;
																				for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


																					if ((i2->sekcija).compare(trenutnaSekcija) == 0) {
																						postojiSekcija = true;

																					}
																				}

																				if (!postojiSekcija) {
																					SadrzajSekcija s = SadrzajSekcija(trenutnaSekcija, "");
																					listaSadrzajaSekcija.push_back(s);
																				}
																			}
																			else {
																				SadrzajSekcija s = SadrzajSekcija(trenutnaSekcija, "");
																				listaSadrzajaSekcija.push_back(s);

																			}


																			list<SadrzajSekcija>::iterator i2;
																			for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


																				if ((i2->sekcija).compare(trenutnaSekcija) == 0) {

																					i2->sadrzaj += "0000";

																				}
																			}
																		}

																	} //else definisan
																	postojiuTabeli = true;
																} // if da li postoji u tabeli simbola

															} //for

															if (!postojiuTabeli) {
																//ne postoji u tabeli, dodati i tabela obracanja unapred
																Simbol s = Simbol(sim, trenutnaSekcija, 0, NULL, 'L', brojacRbr, false, ' ');
																tabelaSimbola.push_back(s);
																brojacRbr++;

																ObracanjeUnapred obracanjeUna = ObracanjeUnapred(sim, locationCounter, 2, trenutnaSekcija, 'w', "");
																tabelaObracanjaUnapred.push_back(obracanjeUna);

																list<Simbol>::iterator i1;
																for (i1 = tabelaSimbola.begin(); i1 != tabelaSimbola.end(); i1++) {
																	if ((i1->ime).compare(sim) == 0) {
																		Relokacija rel = Relokacija(locationCounter, " R_386_32", i1->redniBr, trenutnaSekcija, sim, true);
																		tabelaRealokacije.push_back(rel);


																		bool postojiSekcija = false;
																		if (!listaSadrzajaSekcija.empty()) {

																			list<SadrzajSekcija>::iterator i2;
																			for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


																				if ((i2->sekcija).compare(trenutnaSekcija) == 0) {
																					postojiSekcija = true;

																				}
																			}

																			if (!postojiSekcija) {
																				SadrzajSekcija s = SadrzajSekcija(trenutnaSekcija, "");
																				listaSadrzajaSekcija.push_back(s);
																			}
																		}
																		else {
																			SadrzajSekcija s = SadrzajSekcija(trenutnaSekcija, "");
																			listaSadrzajaSekcija.push_back(s);

																		}



																		list<SadrzajSekcija>::iterator i3;
																		for (i3 = listaSadrzajaSekcija.begin(); i3 != listaSadrzajaSekcija.end(); i3++) {


																			if ((i3->sekcija).compare(trenutnaSekcija) == 0) {

																				i3->sadrzaj += "0000";

																			}
																		}


																	}//if postoji sekcija
																}//for sekcija


															}

															locationCounter += 2;
														}
														else {
															//ako je broj
															long long n = std::stoll(sim, 0, 0);
														//	bool dodajNulu = false;
														//	if (n <= 15) {
														//		dodajNulu = true;
														//	}


															unsigned char b1 = n & 255;
															unsigned char b2 = (n >> 8) & 255;
															if (n < -32768 || n > 32767) {
																cout << "Greska: u direktivi .word literal nije odgovarajuce sirine!" << "\n";
																exit(1);
															}

															string ss;
															ostringstream t;
															t << std::hex << (int)b1;
													/*		if (dodajNulu) {
																ss = "0";
															} */
															string prvi;
															prvi = t.str();
															if (prvi.size() == 1) {
																ss = "0";
															}
															ss += t.str();
															string drugi;
															ostringstream t1;
															t1 << std::hex << (int)b2;
															drugi = t1.str();
															if (drugi.size() == 1) {
																ss += "0";
															}
															ss += t1.str();

															bool postojiSekcija = false;
															if (!listaSadrzajaSekcija.empty()) {

																list<SadrzajSekcija>::iterator i2;
																for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


																	if ((i2->sekcija).compare(trenutnaSekcija) == 0) {
																		postojiSekcija = true;

																	}
																}

																if (!postojiSekcija) {
																	SadrzajSekcija s = SadrzajSekcija(trenutnaSekcija, "");
																	listaSadrzajaSekcija.push_back(s);
																}
															}
															else {
																SadrzajSekcija s = SadrzajSekcija(trenutnaSekcija, "");
																listaSadrzajaSekcija.push_back(s);

															}

															list<SadrzajSekcija>::iterator i2;
															for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {
																//	cout << i2->sekcija << "\n";

																if ((i2->sekcija).compare(trenutnaSekcija) == 0) {
																	//		cout << i2->sekcija<< " 1" <<  "\n";
																	i2->sadrzaj += ss;

																}
															}

															locationCounter += 2;

														}




													} //while
												}
												else {
												if (tok.compare(".equ") == 0) {
													string sim = reci.front();
													reci.erase(reci.begin());
													string prvisim = sim;

													if (sim.find_first_not_of("0123456789") == std::string::npos) {
														cout << "Greska: .equ treba da ima prvi argument koji je simbol!" << "\n";
														exit(1);
													}

													if (reci.empty()) {
														cout << "Greska: .equ treba sadrzi izraz!" << "\n";
														exit(1);
													}

													list<Simbol>::iterator i;
													for (i = tabelaSimbola.begin(); i != tabelaSimbola.end(); i++) {
														if ((i->ime) == sim && i->definisan) {
															cout << "Greska: .equ simbol vec postoji u tabeli simbola!" << "\n";
															exit(1);
														}
														if ((i->ime) == sim && !(i->definisan) && i->tip == 'G') {
															cout << "Greska: .equ simbol vec postoji u tabeli simbola!" << "\n";
															exit(1);
														}
													}

													

													int rez = 0;
													list<string> dodajU;
													list<string> oduzmi;
													list<string> jedanZnak;
													bool prviZnak = false;
													list<string> reci3;
													while (!reci.empty()) {
														string sim = reci.front();
														reci.erase(reci.begin());
														if (!prviZnak) {
															string prvi = sim.substr(0, 1);
															if (prvi.compare("+") == 0 || prvi.compare("-") == 0) {
																cout << "Greska: .equ izraz ne sme da pocne sa - ili +!" << "\n";
																exit(1);
															}
															prviZnak = true;
														}

														

														

														string word = "";
														bool belina = false;
														bool plus = false;
														char prethodniZnak = ' ';
														int n = sim.size();
														int i1 = 0;
														for (auto x : sim)
														{
															i1++;

															if (!reci3.empty() && prethodniZnak == ' ') {
																string t = reci3.back();
																string p1 = t.substr(t.size() - 1, t.size());
																if (p1.compare("+") == 0 || p1.compare("-") == 0) {
																	if (x == '+') {
																		cout << "Greska: .equ dva znaka ne mogu jedno pored drugog!" << "\n";
																		exit(1);
																	} 
																	if (x == '-') {
																		cout << "Greska: .equ dva znaka ne mogu jedno pored drugog!" << "\n";
																		exit(1);
																	}
																}
															}

															if (prethodniZnak == x && x == '+') {
																cout << "Greska: .equ dva znaka ne mogu jedno pored drugog!" << "\n";
																exit(1);
															}

															if (prethodniZnak == x && x == '-') {
																cout << "Greska: .equ dva znaka ne mogu jedno pored drugog!" << "\n";
																exit(1);
															}

															if (x != ' ' &&  x != '+' && x != '-')
															{
																word = word + x;
																belina = true;
																prethodniZnak = x;
															}
															else
															{
																if (belina == true) {
																	if (reci.empty() && (x != '+' ) && i1 == n) {
																		cout << "Greska: .equ na kraju ne moze da se nalazi neki znak!" << "\n";
																		exit(1);
																	}
																	if (reci.empty() && (x != '-') && i1 == n) {
																		cout << "Greska: .equ na kraju ne moze da se nalazi neki znak!" << "\n";
																		exit(1);
																	}
																	if (x != ' ') {
																		word += x;
																	}
																	prethodniZnak = x;
																	reci3.push_back(word);
																	word = "";
																	belina = false;
																}
																else {
																	if (!plus) {
																		if (reci.empty() && i1 == n) {
																			cout << "Greska: .equ na kraju ne moze da se nalazi neki znak!" << "\n";
																			exit(1);
																		}
																		prethodniZnak = x;
																		string t = reci3.back();
																		t += x;
																		reci3.pop_back();
																		reci3.push_back(t);
																		plus = true;
																	}
																}

															}

														} // for
														if (word.compare("") != 0)
															reci3.push_back(word);
														


													} //while


												/*	while (!reci3.empty()) {
														tok = reci3.front();
														reci3.erase(reci3.begin());
														cout << tok << "\n";

													} */

													bool prviZnak1 = false;
													string prethodniZnak = "";
													string sledeciZnak = "";
													bool dodaj = false;
													bool minus = false;
													bool jedanZnak1 = false;
													while (!reci3.empty()) {
														
														if (reci3.size() == 1) {
															jedanZnak1 = true;
														}

														string s = reci3.front();
														reci3.erase(reci3.begin());
														
														prethodniZnak = sledeciZnak;
														sledeciZnak = s.substr(s.size() - 1, s.size());
														if (sledeciZnak.compare("+") == 0 || sledeciZnak.compare("-") == 0) {
															s = s.substr(0, s.size() - 1);
														}
													


														bool hexadecimalan = false;
														string prvi_karakter = s.substr(0, 2);

														if (prvi_karakter.compare("0x") == 0) {
															hexadecimalan = true;
														}


														if (s.find_first_not_of("0123456789") != std::string::npos && !hexadecimalan) {
															//ako je simbol

															list<Simbol>::iterator i;
															bool postojiuTabeli = false;
															for (i = tabelaSimbola.begin(); i != tabelaSimbola.end(); i++) {
																if ((i->ime).compare(s) == 0) {
																	//ako vec postoji u tabeli simbola
																	if (i->definisan) {
																		//definisan i postoji u tabeli

																		unsigned char b1 = i->pomeraj & 255;

																		if (!prviZnak1) {
																			prviZnak1 = true;
																			rez = (int)b1;

																		}
																		else {
																			if (prethodniZnak.compare("+") == 0) {
																				rez = rez + (int)b1;
																			}
																			else {
																				if (prethodniZnak.compare("-") == 0) {
																					rez = rez - (int)b1;
																				}
																			}

																		}

																	}//if definisan
																	else {
																		//postoji u tabeli ali nije definisan, tabela obracanja unapred
																		if (prethodniZnak.compare("+") == 0) {
																			dodajU.push_back(i->ime);
																		}
																		else {
																			if (prethodniZnak.compare("-") == 0) {
																				oduzmi.push_back(i->ime);
																			} 
																		}
																		if (jedanZnak1) {
																			jedanZnak.push_back(i->ime);
																	}
																		



																	}//else definisan
																	postojiuTabeli = true;
																}//if postoji u tabeli
																
															}//for
															if (!postojiuTabeli) {
																//ne postoji u tabeli, dodaj, tabela obracanja unapred
																Simbol s1 = Simbol(s, trenutnaSekcija, 0, NULL, 'L', brojacRbr, false, ' ');
																tabelaSimbola.push_back(s1);
																brojacRbr++;

																if (prethodniZnak.compare("+") == 0) {
																	dodajU.push_back(s);
																}
																else {
																	if (prethodniZnak.compare("-") == 0) {
																		oduzmi.push_back(s);
																	}
																}
															}
														}//if da li je simbol
														else {
															//broj
															long long n = std::stoll(s, 0, 0);
															

															unsigned char b1 = n & 255;
															
															if (!prviZnak1) {
																prviZnak1 = true;
																rez = (int)b1;

															}
															else {
																if (prethodniZnak.compare("+") == 0) {
																	rez = rez + (int)b1;
																}
																else {
																	if (prethodniZnak.compare("-") == 0) {
																		rez = rez - (int)b1;
																	}
																}

															}


															

														}//else broj

													//	cout << rez << "\n";

													}//while


													list<string>::iterator k;
													for (k = dodajU.begin(); k != dodajU.end(); k++) {
														NerazreseniSimboli nerazresenihSimbola = NerazreseniSimboli(prvisim, rez, 0, trenutnaSekcija, 'e', *k);
														tabelaNerazresenihSimbola.push_back(nerazresenihSimbola);
													}
													list<string>::iterator k2;
													for (k2 = oduzmi.begin(); k2 != oduzmi.end(); k2++) {
														NerazreseniSimboli nerazresenihSimbola = NerazreseniSimboli(prvisim, rez, 1, trenutnaSekcija, 'e', *k2);
														tabelaNerazresenihSimbola.push_back(nerazresenihSimbola);
													}
													list<string>::iterator k1;
													for (k1 = jedanZnak.begin(); k1 != jedanZnak.end(); k1++) {
														NerazreseniSimboli nerazresenihSimbola = NerazreseniSimboli(prvisim, rez, 2, trenutnaSekcija, 'e', *k1);
														tabelaNerazresenihSimbola.push_back(nerazresenihSimbola);
													}

													list<Simbol>::iterator il;
													bool postoji = false;
													for (il = tabelaSimbola.begin(); il != tabelaSimbola.end(); il++) {
														if ((il->ime) == sim && !(il->definisan) && il->tip == 'L') {
															postoji = true;
															il->pomeraj = rez;
															il->definisan = true;
															il->sekcija = trenutnaSekcija;
															il->externglobal = 'e';
														}
													}
													if (!postoji) {
														Simbol s1 = Simbol(sim, trenutnaSekcija, rez, NULL, 'L', brojacRbr, true, 'e');

														tabelaSimbola.push_back(s1);
														brojacRbr++;
													}

													


												

												} // if exter
												else {
												if (tok.compare(".end") == 0) {
													if (trenutnaSekcija.compare("UND") != 0) {
														list<Simbol>::iterator i;
														for (i = tabelaSimbola.begin(); i != tabelaSimbola.end(); i++) {
															if ((i->ime).compare(trenutnaSekcija) == 0) {
																i->velicina = locationCounter;
																locationCounter = 0;
															}
														}
													}
												}
												else {
												//	cout << "Greska: ne postoji ovakva direktiva!" << "\n";
												//	exit(1);
											/*		if (tok.compare(".align") == 0) {
														string sim = reci.front();
														reci.erase(reci.begin());

														if (!reci.empty()) {
															cout << "Greska: .skip treba da ima samo jedan literal!" << "\n";
															exit(1);
														}

														if (sim.find_first_not_of("0123456789") != std::string::npos) {
															cout << "Greska: .skip treba da ima samo jedan literal koji je tipa int!" << "\n";
															exit(1);
														}

														int sim1;

														sim1 = stoi(sim); // sim je int

														

													//	locationCounter += (sim1 - locationCounter%sim1)%sim1;

														if (!alignDirective) {
														//	locationCounter += 2;
															locationCounter += 6;
															alignDirective = true;
														}
														else 
															locationCounter += 7;


														/*		while (sim1 > 0) {
																	sim1 = sim1 - 1;
																	sadrzajSekcije += "00";

																}

																*/

													
														
														//alignSim = stoi(sim);
			
														

												//	}//if align */
												//	else {
														cout << "Greska: ne postoji ovakva direktiva!" << "\n";
														exit(1);
												//	}//else align
												} //else end
													} //  else equ
													}//else word
												}//else byte
											}// else skip
										} //else section
									} //else rodata
								} // else bss
							} // else data
						} // else text

					}//else extern


				} // else global


			} //if direktiva
			else {
				//instrukcija
				if (jeInstrukcija(tok, listaInstrukcija)) {

					//dodavanje prvog bajta instrukcije u sadrzaj sekcije
					int kodInstr;
					int velicina;

					list<Instrukcija>::iterator i;

					for (i = listaInstrukcija.begin(); i != listaInstrukcija.end(); i++) {
						if (i->ime.compare(tok) == 0) {
							kodInstr = i->broj;
							if (i->wordByte == 'b') {
								velicina = 0; //byte
							}
							else {
								if (i->wordByte == 'w') {
									velicina = 1; //word
								}
							}

						}
					}


					unsigned char b1 = (kodInstr) & 255;
					unsigned char b2 = (velicina) & 255;

					unsigned char b3 = (kodInstr << 3) xor (velicina << 2) xor 00;

					//cout << "Kod instr " << kodInstr << " velicina " << velicina << " b1 " << std::hex << (int)b1 << " b2 " << std::hex << (int)b2 << " b3 " << std::hex << (int)b3 << "\n";

					string ss;
					ostringstream t;
					t << std::hex << (int)b3;


					ss = t.str();


					bool postojiSekcija = false;
					if (!listaSadrzajaSekcija.empty()) {

						list<SadrzajSekcija>::iterator i2;
						for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


							if ((i2->sekcija).compare(trenutnaSekcija) == 0) {
								postojiSekcija = true;

							}
						}

						if (!postojiSekcija) {
							SadrzajSekcija s = SadrzajSekcija(trenutnaSekcija, "");
							listaSadrzajaSekcija.push_back(s);
						}
					}
					else {
						SadrzajSekcija s = SadrzajSekcija(trenutnaSekcija, "");
						listaSadrzajaSekcija.push_back(s);

					}




					list<SadrzajSekcija>::iterator i2;
					for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


						if ((i2->sekcija).compare(trenutnaSekcija) == 0) {

							i2->sadrzaj += ss;

						}
					}

					locationCounter += 1;
					//zavrseno dodavanje prvog bajta instrukcije



					if (tok.compare("xchg") == 0 || tok.compare("xchgb") == 0 || tok.compare("mov") == 0 || tok.compare("movb") == 0 || tok.compare("add") == 0 || tok.compare("addb") == 0
						|| tok.compare("sub") == 0 || tok.compare("subb") == 0 || tok.compare("mul") == 0 || tok.compare("mulb") == 0 || tok.compare("div") == 0 || tok.compare("divb") == 0
						|| tok.compare("cmp") == 0 || tok.compare("cmpb") == 0 || tok.compare("not") == 0 || tok.compare("notb") == 0 || tok.compare("and") == 0 || tok.compare("andb") == 0
						|| tok.compare("or") == 0 || tok.compare("orb") == 0 || tok.compare("xor") == 0 || tok.compare("xorb") == 0 || tok.compare("test") == 0 || tok.compare("testb") == 0
						|| tok.compare("shl") == 0 || tok.compare("shlb") == 0 || tok.compare("shr") == 0 || tok.compare("shrb") == 0) {
						if (reci.size() != 2) {
							cout << "Greska instrukcija: " << tok << " treba da ima tacno dva operanda!" << "\n";
							exit(1);
						}
					}

					if (tok.compare("int") == 0 || tok.compare("intb") == 0 || tok.compare("call") == 0 || tok.compare("callb") == 0 || tok.compare("jmp") == 0 || tok.compare("jmpb") == 0
						|| tok.compare("jeq") == 0 || tok.compare("jeqb") == 0 || tok.compare("jne") == 0 || tok.compare("jneb") == 0 || tok.compare("jgt") == 0 || tok.compare("jgtb") == 0
						|| tok.compare("push") == 0 || tok.compare("pushb") == 0 || tok.compare("pop") == 0 || tok.compare("popb") == 0) {
						if (reci.size() != 1) {
							cout << "Greska instrukcija: " << tok << " treba da ima samo jedan operand!" << "\n";
							exit(1);
						}
					}

					if (tok.compare("halt") == 0 || tok.compare("haltb") == 0 || tok.compare("iret") == 0 || tok.compare("iretb") == 0 || tok.compare("ret") == 0 || tok.compare("retb") == 0) {
						if (!reci.empty()) {
							cout << "Greska instrukcija: " << tok << " nema operande!" << "\n";
							exit(1);
						}
					}

					if(tok.compare("halt") == 0 || tok.compare("haltb") == 0 || tok.compare("iret") == 0 || tok.compare("iretb") == 0 || tok.compare("ret") == 0 || tok.compare("retb") == 0) 
					{ }
					else 
					{

					string sim = reci.front();
					reci.erase(reci.begin());



					if (tok.compare("xchg") == 0 || tok.compare("xchgb") == 0 || tok.compare("mov") == 0 || tok.compare("movb") == 0 || tok.compare("add") == 0 || tok.compare("addb") == 0
						|| tok.compare("sub") == 0 || tok.compare("subb") == 0 || tok.compare("mul") == 0 || tok.compare("mulb") == 0 || tok.compare("div") == 0 || tok.compare("divb") == 0
						|| tok.compare("cmp") == 0 || tok.compare("cmpb") == 0 || tok.compare("not") == 0 || tok.compare("notb") == 0 || tok.compare("and") == 0 || tok.compare("andb") == 0
						|| tok.compare("or") == 0 || tok.compare("orb") == 0 || tok.compare("xor") == 0 || tok.compare("xorb") == 0 || tok.compare("test") == 0 || tok.compare("testb") == 0
						|| tok.compare("shl") == 0 || tok.compare("shlb") == 0 || tok.compare("shr") == 0 || tok.compare("shrb") == 0) {

						string op1;
					//	cout << "Instrukcija: " << tok << "\n";

						
							op1 = odrediAdresiranje(sim);

							if (tok.compare("shr") == 0 || tok.compare("shrb") == 0) {
								if (op1.compare("neposredno") == 0) {
									cout << "Greska: kod instrukcije shr prvi operand je dest" << "\n";
									exit(1);
								}

							} // if shr
						

						if (op1.compare("neposredno") == 0) {
							//neposredno adresiranje


							int adresiranje = 0;
							int reg = 0;

							unsigned char b1 = (adresiranje) & 255;
							unsigned char b2 = (reg) & 255;

							unsigned char b4 = (adresiranje << 5) xor (reg << 1) xor 0;

							string ss1;
							ostringstream t1;
							t1 << std::hex << (int)b4;
							string prvi;
							prvi = t1.str();
							if (prvi.size() == 1) {
								ss1 = "0";
							}

							ss1 += t1.str();


							list<SadrzajSekcija>::iterator i2;
							for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


								if ((i2->sekcija).compare(trenutnaSekcija) == 0) {

									i2->sadrzaj += ss1;

								}
							}

							locationCounter += 1;
							//zavrseno dodavanje prvog bajta adresiranja za neposredno

							if (velicina == 0) {
								//byte
								string rec1 = sim.substr(0, 1);

								//proveri da li je znak broj ili simbol
								bool hexadecimalan = false;
								string prvi_karakter = sim.substr(1, 2);
								sim = sim.substr(1, sim.size());

								if (prvi_karakter.compare("0x") == 0) {
									hexadecimalan = true;
								}


								if (sim.find_first_not_of("0123456789") != std::string::npos && !hexadecimalan) {
									//simbol

									list<Simbol>::iterator i;
									bool postojiuTabeli = false;
									for (i = tabelaSimbola.begin(); i != tabelaSimbola.end(); i++) {
										if (i->ime.compare(sim) == 0) {
											//ako vec postoji u tabeli simbola
											if (i->definisan) {
												//definisan
												if ((i->tip) == 'L') {
													//ako je local
													list<Simbol>::iterator i1;
													for (i1 = tabelaSimbola.begin(); i1 != tabelaSimbola.end(); i1++) {
														if ((i1->sekcija).compare(i->sekcija) == 0 && (i1->ime).compare(i->sekcija) == 0) {
															Relokacija rel = Relokacija(locationCounter, " R_386_32", i1->redniBr, trenutnaSekcija, sim, false);
															tabelaRealokacije.push_back(rel);


															bool dodajNulu = false;
															if (i->pomeraj <= 15) {
																dodajNulu = true;
															}

															unsigned char b1 = i->pomeraj & 255;
															if (i->pomeraj < -128 || i->pomeraj > 127) {
																cout << "Greska: literal u neposrednom adresiranju mora da bude jedan bajt, zato sto je instrukcija bajtovska!" << "\n";
																exit(1);
															}

															string ss;
															ostringstream t;
															t << std::hex << (int)b1;

															if (dodajNulu) {
																ss = "0";
															}
															ss += t.str();

															list<SadrzajSekcija>::iterator i2;
															for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


																if ((i2->sekcija).compare(trenutnaSekcija) == 0) {

																	i2->sadrzaj += ss;

																}
															}



														}//if postoji sekcija
													}//for sekcija
												}//if local
												else { //ako je global
													int redniBr = i->redniBr;
													Relokacija rel = Relokacija(locationCounter, " R_386_32", i->redniBr, trenutnaSekcija, "", false);
													tabelaRealokacije.push_back(rel);


													list<SadrzajSekcija>::iterator i2;
													for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


														if ((i2->sekcija).compare(trenutnaSekcija) == 0) {

															i2->sadrzaj += "00";

														}
													}
												}

											} //if definisan
											else {
												//postoji u tabeli ali nije definisan tabela obracanja unapred
												if ((i->tip) == 'L') {
													//dodaj novu bool vrednost u tabelu simbola da oznaci da treba da uradi i->pomeraj & 255; a ne samo da upise pomeraj

													ObracanjeUnapred obracanjeUna = ObracanjeUnapred(sim, locationCounter, 1, trenutnaSekcija, 'b', "");
													tabelaObracanjaUnapred.push_back(obracanjeUna);

													list<Simbol>::iterator i1;
													for (i1 = tabelaSimbola.begin(); i1 != tabelaSimbola.end(); i1++) {
														if ((i1->ime).compare(i->ime) == 0) {
															Relokacija rel = Relokacija(locationCounter, " R_386_32", i1->redniBr, trenutnaSekcija, sim, true);
															tabelaRealokacije.push_back(rel);


															list<SadrzajSekcija>::iterator i2;
															for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


																if ((i2->sekcija).compare(trenutnaSekcija) == 0) {

																	i2->sadrzaj += "00";

																}
															}


														}//if postoji sekcija
													}//for sekcija

												}
												else {
													//ako je global sve isto, ne dodajem u tabeli obracanja unapred
													int redniBr = i->redniBr;
													Relokacija rel = Relokacija(locationCounter, " R_386_32", i->redniBr, trenutnaSekcija, "", false);
													tabelaRealokacije.push_back(rel);

													list<SadrzajSekcija>::iterator i2;
													for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


														if ((i2->sekcija).compare(trenutnaSekcija) == 0) {

															i2->sadrzaj += "00";

														}
													}
												}

											} //else definisan
											postojiuTabeli = true;
										} // if da li postoji u tabeli simbola

									} //for

									if (!postojiuTabeli) {
										//ne postoji u tabeli, dodati i tabela obracanja unapred
										Simbol s = Simbol(sim, trenutnaSekcija, 0, NULL, 'L', brojacRbr, false, ' ');
										tabelaSimbola.push_back(s);
										brojacRbr++;

										ObracanjeUnapred obracanjeUna = ObracanjeUnapred(sim, locationCounter, 1, trenutnaSekcija, 'b', "");
										tabelaObracanjaUnapred.push_back(obracanjeUna);

										list<Simbol>::iterator i1;
										for (i1 = tabelaSimbola.begin(); i1 != tabelaSimbola.end(); i1++) {
											if ((i1->ime).compare(sim) == 0) {
												Relokacija rel = Relokacija(locationCounter, " R_386_32", i1->redniBr, trenutnaSekcija, sim, true);
												tabelaRealokacije.push_back(rel);


												list<SadrzajSekcija>::iterator i3;
												for (i3 = listaSadrzajaSekcija.begin(); i3 != listaSadrzajaSekcija.end(); i3++) {


													if ((i3->sekcija).compare(trenutnaSekcija) == 0) {

														i3->sadrzaj += "00";

													}
												}


											}//if postoji sekcija
										}//for sekcija


									}//if postoji



								}
								else {
									//broj
									long long n = std::stoll(sim, 0, 0);
									bool dodajNulu = false;
									if (n <= 15) {
										dodajNulu = true;
									}

									unsigned char b1 = n & 255;
									if (n < -128 || n > 127) {
										cout << "Greska: literal u neposrednom adresiranju mora da bude jedan bajt, zato sto je instrukcija bajtovska!" << "\n";
										exit(1);
									}

									string ss;
									ostringstream t;
									t << std::hex << (int)b1;

									if (dodajNulu) {
										ss = "0";
									}
									ss += t.str();



									list<SadrzajSekcija>::iterator i2;
									for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {
										//	cout << i2->sekcija << "\n";

										if ((i2->sekcija).compare(trenutnaSekcija) == 0) {
											//		cout << i2->sekcija<< " 1" <<  "\n";
											i2->sadrzaj += ss;

										}
									}

								}//else broj


								locationCounter += 1;
							} //if velicina = 0 byte
							else {
								if (velicina == 1) {

									neposrednoAdresiranje(sim, trenutnaSekcija, locationCounter, brojacRbr, tabelaObracanjaUnapred, tabelaSimbola, tabelaRealokacije, listaSadrzajaSekcija);
									locationCounter += 2;

								}//if vel = 1 word
							}//else velicina = 0 byte

						}//if neposredno
						else {
							if (op1.compare("memdir") == 0) {
								//neposredno adresiranje
								int adresiranje = 4;
								int reg = 0;

								unsigned char b1 = (adresiranje) & 255;
								unsigned char b2 = (reg) & 255;

								unsigned char b4 = (adresiranje << 5) xor (reg << 1) xor 0;

								string ss1;
								ostringstream t1;
								t1 << std::hex << (int)b4;
								string prvi;
								prvi = t1.str();
								if (prvi.size() == 1) {
									ss1 = "0";
								}

								ss1 += t1.str();


								list<SadrzajSekcija>::iterator i2;
								for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


									if ((i2->sekcija).compare(trenutnaSekcija) == 0) {

										i2->sadrzaj += ss1;

									}
								}

								locationCounter += 1;
								//zavrseno dodavanje prvog bajta adresiranja za neposredno


								memorijskoAdresiranje(sim, trenutnaSekcija, locationCounter, brojacRbr, tabelaObracanjaUnapred, tabelaSimbola, tabelaRealokacije, listaSadrzajaSekcija);
								locationCounter += 2;
							}//if memdir
							else {
								if (op1.compare("regdir") == 0) {
									//neposredno adresiranje
									int high = 0;
									int adresiranje = 1;
									int reg;
									sim = sim.substr(1, sim.size());
									if (sim.size() == 2) {
										if (velicina == 0) {
											cout << "Greska: instrukcija je byte, a operand je word!" << "\n";
											exit(1);
										}
										string broj = sim.substr(1, 2);
										int br = std::stoi(broj);
										reg = br;
									}
									else {
										if (sim.size() == 3) {
											if (velicina == 1) {
												cout << "Greska: instrukcija je word, a operand je byte!" << "\n";
												exit(1);
											}

											string broj = sim.substr(1, 2);
											int br = std::stoi(broj);
											reg = br;

											string hl = sim.substr(2, 3);
											if (hl.compare("h") == 0) {
												high = 1;
											}
											else {
												high = 0;
											}

										}
									}



									unsigned char b1 = (adresiranje) & 255;
									unsigned char b2 = (reg) & 255;

									unsigned char b4 = (adresiranje << 5) xor (reg << 1) xor high;

									string ss1;
									ostringstream t1;
									t1 << std::hex << (int)b4;
									string prvi;
									prvi = t1.str();
									if (prvi.size() == 1) {
										ss1 = "0";
									}

									ss1 += t1.str();


									list<SadrzajSekcija>::iterator i2;
									for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


										if ((i2->sekcija).compare(trenutnaSekcija) == 0) {

											i2->sadrzaj += ss1;

										}
									}

									locationCounter += 1;
									//zavrseno dodavanje prvog bajta adresiranja za neposredno
								}//if regdir
								else {
									if (op1.compare("regind") == 0) {
										//neposredno adresiranje
										int high = 0;
										int adresiranje = 2;
										int reg;

										sim = sim.substr(1, sim.size());

										sim = sim.substr(1, sim.size() - 2);

										string broj = sim.substr(1, 2);
										int br = std::stoi(broj);
										reg = br;


										unsigned char b1 = (adresiranje) & 255;
										unsigned char b2 = (reg) & 255;

										unsigned char b4 = (adresiranje << 5) xor (reg << 1) xor high;

										string ss1;
										ostringstream t1;
										t1 << std::hex << (int)b4;
										string prvi;
										prvi = t1.str();
										if (prvi.size() == 1) {
											ss1 = "0";
										}

										ss1 += t1.str();


										list<SadrzajSekcija>::iterator i2;
										for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


											if ((i2->sekcija).compare(trenutnaSekcija) == 0) {

												i2->sadrzaj += ss1;

											}
										}


										locationCounter += 1;
									}//if regind
									else {
										if (op1.compare("regindpom") == 0) {
											string word = "";
											bool zagrada = false;
											for (auto x : sim)
											{

												if (x != '(' && !zagrada)
												{
													word = word + x;

												}
												else
												{
													zagrada = true;

												}

											} //for


											int high = 0;
											int adresiranje = 3;
											int reg;

											sim = sim.substr(word.size(), sim.size());

											sim = sim.substr(1, sim.size());

											sim = sim.substr(1, sim.size() - 2);

											string broj = sim.substr(1, 2);
											int br = std::stoi(broj);
											reg = br;


											unsigned char b1 = (adresiranje) & 255;
											unsigned char b2 = (reg) & 255;

											unsigned char b4 = (adresiranje << 5) xor (reg << 1) xor high;

											string ss1;
											ostringstream t1;
											t1 << std::hex << (int)b4;
											string prvi;
											prvi = t1.str();
											if (prvi.size() == 1) {
												ss1 = "0";
											}

											ss1 += t1.str();


											list<SadrzajSekcija>::iterator i2;
											for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


												if ((i2->sekcija).compare(trenutnaSekcija) == 0) {

													i2->sadrzaj += ss1;

												}
											}

											locationCounter += 1;

											memorijskoAdresiranje(word, trenutnaSekcija, locationCounter, brojacRbr, tabelaObracanjaUnapred, tabelaSimbola, tabelaRealokacije, listaSadrzajaSekcija);
											locationCounter += 2;


										}//if regindpom
										else {
											if (op1.compare("pcrel") == 0) {
												string word = "";
												bool zagrada = false;
												for (auto x : sim)
												{

													if (x != '(' && !zagrada)
													{
														word = word + x;

													}
													else
													{
														zagrada = true;

													}

												} //for


												int high = 0;
												int adresiranje = 3;
												int reg = 7;

												sim = sim.substr(word.size(), sim.size());



												unsigned char b1 = (adresiranje) & 255;
												unsigned char b2 = (reg) & 255;

												unsigned char b4 = (adresiranje << 5) xor (reg << 1) xor high;

												string ss1;
												ostringstream t1;
												t1 << std::hex << (int)b4;
												string prvi;
												prvi = t1.str();
												if (prvi.size() == 1) {
													ss1 = "0";
												}

												ss1 += t1.str();


												list<SadrzajSekcija>::iterator i2;
												for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


													if ((i2->sekcija).compare(trenutnaSekcija) == 0) {

														i2->sadrzaj += ss1;

													}
												}

												locationCounter += 1;

												pcrelativnoAdresiranje(word, trenutnaSekcija, locationCounter, brojacRbr, tabelaObracanjaUnapred, tabelaSimbola, tabelaRealokacije, listaSadrzajaSekcija);
												locationCounter += 2;

											}//if pc relativno
										}//else regindpom
									}//else regind

								}//else regdir
							}//else memdir
						}//else neposredno
				
						
							sim = reci.front();
							reci.erase(reci.begin());

						string	op2 = odrediAdresiranje(sim);
						
						if (tok.compare("shr") == 0 || tok.compare("shrb") == 0) {
							if (op2.compare("neposredno") == 0) {
								//neposredno adresiranje


								int adresiranje = 0;
								int reg = 0;

								unsigned char b1 = (adresiranje) & 255;
								unsigned char b2 = (reg) & 255;

								unsigned char b4 = (adresiranje << 5) xor (reg << 1) xor 0;

								string ss1;
								ostringstream t1;
								t1 << std::hex << (int)b4;
								string prvi;
								prvi = t1.str();
								if (prvi.size() == 1) {
									ss1 = "0";
								}

								ss1 += t1.str();


								list<SadrzajSekcija>::iterator i2;
								for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


									if ((i2->sekcija).compare(trenutnaSekcija) == 0) {

										i2->sadrzaj += ss1;

									}
								}

								locationCounter += 1;
								//zavrseno dodavanje prvog bajta adresiranja za neposredno

								if (velicina == 0) {
									//byte
									string rec1 = sim.substr(0, 1);

									//proveri da li je znak broj ili simbol
									bool hexadecimalan = false;
									string prvi_karakter = sim.substr(1, 2);
									sim = sim.substr(1, sim.size());

									if (prvi_karakter.compare("0x") == 0) {
										hexadecimalan = true;
									}


									if (sim.find_first_not_of("0123456789") != std::string::npos && !hexadecimalan) {
										//simbol

										list<Simbol>::iterator i;
										bool postojiuTabeli = false;
										for (i = tabelaSimbola.begin(); i != tabelaSimbola.end(); i++) {
											if (i->ime.compare(sim) == 0) {
												//ako vec postoji u tabeli simbola
												if (i->definisan) {
													//definisan
													if ((i->tip) == 'L') {
														//ako je local
														list<Simbol>::iterator i1;
														for (i1 = tabelaSimbola.begin(); i1 != tabelaSimbola.end(); i1++) {
															if ((i1->sekcija).compare(i->sekcija) == 0 && (i1->ime).compare(i->sekcija) == 0) {
																Relokacija rel = Relokacija(locationCounter, " R_386_32", i1->redniBr, trenutnaSekcija, sim, false);
																tabelaRealokacije.push_back(rel);


																bool dodajNulu = false;
																if (i->pomeraj <= 15) {
																	dodajNulu = true;
																}

																unsigned char b1 = i->pomeraj & 255;
																if (i->pomeraj < -128 || i->pomeraj > 127) {
																	cout << "Greska: literal u neposrednom adresiranju mora da bude jedan bajt, zato sto je instrukcija bajtovska!" << "\n";
																	exit(1);
																}

																string ss;
																ostringstream t;
																t << std::hex << (int)b1;

																if (dodajNulu) {
																	ss = "0";
																}
																ss += t.str();

																list<SadrzajSekcija>::iterator i2;
																for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


																	if ((i2->sekcija).compare(trenutnaSekcija) == 0) {

																		i2->sadrzaj += ss;

																	}
																}



															}//if postoji sekcija
														}//for sekcija
													}//if local
													else { //ako je global
														int redniBr = i->redniBr;
														Relokacija rel = Relokacija(locationCounter, " R_386_32", i->redniBr, trenutnaSekcija, "", false);
														tabelaRealokacije.push_back(rel);


														list<SadrzajSekcija>::iterator i2;
														for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


															if ((i2->sekcija).compare(trenutnaSekcija) == 0) {

																i2->sadrzaj += "00";

															}
														}
													}

												} //if definisan
												else {
													//postoji u tabeli ali nije definisan tabela obracanja unapred
													if ((i->tip) == 'L') {
														//dodaj novu bool vrednost u tabelu simbola da oznaci da treba da uradi i->pomeraj & 255; a ne samo da upise pomeraj

														ObracanjeUnapred obracanjeUna = ObracanjeUnapred(sim, locationCounter, 1, trenutnaSekcija, 'b', "");
														tabelaObracanjaUnapred.push_back(obracanjeUna);

														list<Simbol>::iterator i1;
														for (i1 = tabelaSimbola.begin(); i1 != tabelaSimbola.end(); i1++) {
															if ((i1->ime).compare(i->ime) == 0) {
																Relokacija rel = Relokacija(locationCounter, " R_386_32", i1->redniBr, trenutnaSekcija, sim, true);
																tabelaRealokacije.push_back(rel);


																list<SadrzajSekcija>::iterator i2;
																for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


																	if ((i2->sekcija).compare(trenutnaSekcija) == 0) {

																		i2->sadrzaj += "00";

																	}
																}


															}//if postoji sekcija
														}//for sekcija

													}
													else {
														//ako je global sve isto, ne dodajem u tabeli obracanja unapred
														int redniBr = i->redniBr;
														Relokacija rel = Relokacija(locationCounter, " R_386_32", i->redniBr, trenutnaSekcija, "", false);
														tabelaRealokacije.push_back(rel);

														list<SadrzajSekcija>::iterator i2;
														for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


															if ((i2->sekcija).compare(trenutnaSekcija) == 0) {

																i2->sadrzaj += "00";

															}
														}
													}

												} //else definisan
												postojiuTabeli = true;
											} // if da li postoji u tabeli simbola

										} //for

										if (!postojiuTabeli) {
											//ne postoji u tabeli, dodati i tabela obracanja unapred
											Simbol s = Simbol(sim, trenutnaSekcija, 0, NULL, 'L', brojacRbr, false, ' ');
											tabelaSimbola.push_back(s);
											brojacRbr++;

											ObracanjeUnapred obracanjeUna = ObracanjeUnapred(sim, locationCounter, 1, trenutnaSekcija, 'b', "");
											tabelaObracanjaUnapred.push_back(obracanjeUna);

											list<Simbol>::iterator i1;
											for (i1 = tabelaSimbola.begin(); i1 != tabelaSimbola.end(); i1++) {
												if ((i1->ime).compare(sim) == 0) {
													Relokacija rel = Relokacija(locationCounter, " R_386_32", i1->redniBr, trenutnaSekcija, sim, true);
													tabelaRealokacije.push_back(rel);


													list<SadrzajSekcija>::iterator i3;
													for (i3 = listaSadrzajaSekcija.begin(); i3 != listaSadrzajaSekcija.end(); i3++) {


														if ((i3->sekcija).compare(trenutnaSekcija) == 0) {

															i3->sadrzaj += "00";

														}
													}


												}//if postoji sekcija
											}//for sekcija


										}//if postoji



									}
									else {
										//broj
										long long n = std::stoll(sim, 0, 0);
										bool dodajNulu = false;
										if (n <= 15) {
											dodajNulu = true;
										}

										unsigned char b1 = n & 255;
										if (n < -128 || n > 127) {
											cout << "Greska: literal u neposrednom adresiranju mora da bude jedan bajt, zato sto je instrukcija bajtovska!" << "\n";
											exit(1);
										}

										string ss;
										ostringstream t;
										t << std::hex << (int)b1;

										if (dodajNulu) {
											ss = "0";
										}
										ss += t.str();



										list<SadrzajSekcija>::iterator i2;
										for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {
											//	cout << i2->sekcija << "\n";

											if ((i2->sekcija).compare(trenutnaSekcija) == 0) {
												//		cout << i2->sekcija<< " 1" <<  "\n";
												i2->sadrzaj += ss;

											}
										}

									}//else broj


									locationCounter += 1;
								} //if velicina = 0 byte
								else {
									if (velicina == 1) {

										neposrednoAdresiranje(sim, trenutnaSekcija, locationCounter, brojacRbr, tabelaObracanjaUnapred, tabelaSimbola, tabelaRealokacije, listaSadrzajaSekcija);
										locationCounter += 2;

									}//if vel = 1 word
								}//else velicina = 0 byte

							}//if neposredno
							

						} // if shr


						

					
					if (op2.compare("neposredno") == 0 && tok.compare("shr") != 0 && tok.compare("shrb") != 0) {
						cout << "Greska:  destinacioni registar ne moze sa neposrednim adresiranjem!" << "\n";
						exit(1);
					}
					if (op2.compare("memdir") == 0) {
						//neposredno adresiranje
						int adresiranje = 4;
						int reg = 0;

						unsigned char b1 = (adresiranje) & 255;
						unsigned char b2 = (reg) & 255;

						unsigned char b4 = (adresiranje << 5) xor (reg << 1) xor 0;

						string ss1;
						ostringstream t1;
						t1 << std::hex << (int)b4;
						string prvi;
						prvi = t1.str();
						if (prvi.size() == 1) {
							ss1 = "0";
						}

						ss1 += t1.str();


						list<SadrzajSekcija>::iterator i2;
						for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


							if ((i2->sekcija).compare(trenutnaSekcija) == 0) {

								i2->sadrzaj += ss1;

							}
						}

						locationCounter += 1;
						//zavrseno dodavanje prvog bajta adresiranja za neposredno

						memorijskoAdresiranje(sim, trenutnaSekcija, locationCounter, brojacRbr, tabelaObracanjaUnapred, tabelaSimbola, tabelaRealokacije, listaSadrzajaSekcija);
						locationCounter += 2;

					}//if memdir
					else {
						if (op2.compare("regdir") == 0) {
							//neposredno adresiranje
							int high = 0;
							int adresiranje = 1;
							int reg;
							sim = sim.substr(1, sim.size());
							//cout << "reg " << sim << "\n";
							if (sim.size() == 2) {
								if (velicina == 0) {
									cout << "Greska: instrukcija je byte, a operand je word!" << "\n";
									exit(3);
								}
								string broj = sim.substr(1, 2);
								int br = std::stoi(broj);
								reg = br;
							}
							else {
								if (sim.size() == 3) {
									if (velicina == 1) {
										//cout << "Instrukcija " << tok << "\n";
										cout << "Greska: instrukcija je word, a operand je byte!" << "\n";
										exit(3);
									}

									string broj = sim.substr(1, 2);
									int br = std::stoi(broj);
									reg = br;

									string hl = sim.substr(2, 3);
									if (hl.compare("h") == 0) {
										high = 1;
									}
									else {
										high = 0;
									}

								}
							}



							unsigned char b1 = (adresiranje) & 255;
							unsigned char b2 = (reg) & 255;

							unsigned char b4 = (adresiranje << 5) xor (reg << 1) xor high;

							string ss1;
							ostringstream t1;
							t1 << std::hex << (int)b4;
							string prvi;
							prvi = t1.str();
							if (prvi.size() == 1) {
								ss1 = "0";
							}

							ss1 += t1.str();


							list<SadrzajSekcija>::iterator i2;
							for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


								if ((i2->sekcija).compare(trenutnaSekcija) == 0) {

									i2->sadrzaj += ss1;

								}
							}

							locationCounter += 1;
							//zavrseno dodavanje prvog bajta adresiranja za neposredno
						}//if regdir
						else {
							if (op2.compare("regind") == 0) {
								//neposredno adresiranje
								int high = 0;
								int adresiranje = 2;
								int reg;

								sim = sim.substr(1, sim.size());

								sim = sim.substr(1, sim.size() - 2);

								string broj = sim.substr(1, 2);
								int br = std::stoi(broj);
								reg = br;


								unsigned char b1 = (adresiranje) & 255;
								unsigned char b2 = (reg) & 255;

								unsigned char b4 = (adresiranje << 5) xor (reg << 1) xor high;

								string ss1;
								ostringstream t1;
								t1 << std::hex << (int)b4;
								string prvi;
								prvi = t1.str();
								if (prvi.size() == 1) {
									ss1 = "0";
								}

								ss1 += t1.str();


								list<SadrzajSekcija>::iterator i2;
								for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


									if ((i2->sekcija).compare(trenutnaSekcija) == 0) {

										i2->sadrzaj += ss1;

									}
								}


								locationCounter += 1;
							}//if regind
							else {
								if (op2.compare("regindpom") == 0) {
									string word = "";
									bool zagrada = false;
									for (auto x : sim)
									{

										if (x != '(' && !zagrada)
										{
											word = word + x;

										}
										else
										{
											zagrada = true;

										}

									} //for


									int high = 0;
									int adresiranje = 3;
									int reg;

									sim = sim.substr(word.size(), sim.size());

									sim = sim.substr(1, sim.size());

									sim = sim.substr(1, sim.size() - 2);

									string broj = sim.substr(1, 2);
									int br = std::stoi(broj);
									reg = br;


									unsigned char b1 = (adresiranje) & 255;
									unsigned char b2 = (reg) & 255;

									unsigned char b4 = (adresiranje << 5) xor (reg << 1) xor high;

									string ss1;
									ostringstream t1;
									t1 << std::hex << (int)b4;
									string prvi;
									prvi = t1.str();
									if (prvi.size() == 1) {
										ss1 = "0";
									}

									ss1 += t1.str();


									list<SadrzajSekcija>::iterator i2;
									for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


										if ((i2->sekcija).compare(trenutnaSekcija) == 0) {

											i2->sadrzaj += ss1;

										}
									}

									locationCounter += 1;

									memorijskoAdresiranje(word, trenutnaSekcija, locationCounter, brojacRbr, tabelaObracanjaUnapred, tabelaSimbola, tabelaRealokacije, listaSadrzajaSekcija);
									locationCounter += 2;


								}//if regindpom
								else {
									if (op2.compare("pcrel") == 0) {
										string word = "";
										bool zagrada = false;
										for (auto x : sim)
										{

											if (x != '(' && !zagrada)
											{
												word = word + x;

											}
											else
											{
												zagrada = true;

											}

										} //for


										int high = 0;
										int adresiranje = 3;
										int reg = 7;

										sim = sim.substr(word.size(), sim.size());



										unsigned char b1 = (adresiranje) & 255;
										unsigned char b2 = (reg) & 255;

										unsigned char b4 = (adresiranje << 5) xor (reg << 1) xor high;

										string ss1;
										ostringstream t1;
										t1 << std::hex << (int)b4;
										string prvi;
										prvi = t1.str();
										if (prvi.size() == 1) {
											ss1 = "0";
										}

										ss1 += t1.str();


										list<SadrzajSekcija>::iterator i2;
										for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


											if ((i2->sekcija).compare(trenutnaSekcija) == 0) {

												i2->sadrzaj += ss1;

											}
										}

										locationCounter += 1;

										pcrelativnoAdresiranje(word, trenutnaSekcija, locationCounter, brojacRbr, tabelaObracanjaUnapred, tabelaSimbola, tabelaRealokacije, listaSadrzajaSekcija);
										locationCounter += 2;

									}//if pc relativno
								}//else regindpom
							}//else regind
						}//else regdir
					}//else memdir
					

				} //instrukcije sa 2 operanda
				else {
				if (tok.compare("int") == 0 || tok.compare("intb") == 0  || tok.compare("pop") == 0 || tok.compare("popb") == 0) {
				//	cout << "Instrukcija: " << tok <<" "<<sim   << "\n";


					string op2 = odrediAdresiranje(sim);
					if (op2.compare("neposredno") == 0) {
						cout << "Greska:  destinacioni registar ne moze sa neposrednim adresiranjem!" << "\n";
						exit(1);
					}
					if (op2.compare("memdir") == 0) {
						//neposredno adresiranje
						int adresiranje = 4;
						int reg = 0;

						unsigned char b1 = (adresiranje) & 255;
						unsigned char b2 = (reg) & 255;

						unsigned char b4 = (adresiranje << 5) xor (reg << 1) xor 0;

						string ss1;
						ostringstream t1;
						t1 << std::hex << (int)b4;
						string prvi;
						prvi = t1.str();
						if (prvi.size() == 1) {
							ss1 = "0";
						}

						ss1 += t1.str();


						list<SadrzajSekcija>::iterator i2;
						for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


							if ((i2->sekcija).compare(trenutnaSekcija) == 0) {

								i2->sadrzaj += ss1;

							}
						}

						locationCounter += 1;
						//zavrseno dodavanje prvog bajta adresiranja za neposredno

						memorijskoAdresiranje(sim, trenutnaSekcija, locationCounter, brojacRbr, tabelaObracanjaUnapred, tabelaSimbola, tabelaRealokacije, listaSadrzajaSekcija);
						locationCounter += 2;

					}//if memdir
					else {
						if (op2.compare("regdir") == 0) {
							//neposredno adresiranje
							int high = 0;
							int adresiranje = 1;
							int reg;
							sim = sim.substr(1, sim.size());
							if (sim.size() == 2) {
								if (velicina == 0) {
									cout << "Greska: instrukcija je byte, a operand je word!" << "\n";
									exit(1);
								}
								string broj = sim.substr(1, 2);
								int br = std::stoi(broj);
								reg = br;
							}
							else {
								if (sim.size() == 3) {
									if (velicina == 1) {
										cout << "Greska: instrukcija je word, a operand je byte!" << "\n";
										exit(1);
									}

									string broj = sim.substr(1, 2);
									int br = std::stoi(broj);
									reg = br;

									string hl = sim.substr(2, 3);
									if (hl.compare("h") == 0) {
										high = 1;
									}
									else {
										high = 0;
									}

								}
							}



							unsigned char b1 = (adresiranje) & 255;
							unsigned char b2 = (reg) & 255;

							unsigned char b4 = (adresiranje << 5) xor (reg << 1) xor high;

							string ss1;
							ostringstream t1;
							t1 << std::hex << (int)b4;
							string prvi;
							prvi = t1.str();
							if (prvi.size() == 1) {
								ss1 = "0";
							}

							ss1 += t1.str();


							list<SadrzajSekcija>::iterator i2;
							for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


								if ((i2->sekcija).compare(trenutnaSekcija) == 0) {

									i2->sadrzaj += ss1;

								}
							}

							locationCounter += 1;
							//zavrseno dodavanje prvog bajta adresiranja za neposredno
						}//if regdir
						else {
							if (op2.compare("regind") == 0) {
								//neposredno adresiranje
								int high = 0;
								int adresiranje = 2;
								int reg;

								sim = sim.substr(1, sim.size());

								sim = sim.substr(1, sim.size() - 2);

								string broj = sim.substr(1, 2);
								int br = std::stoi(broj);
								reg = br;


								unsigned char b1 = (adresiranje) & 255;
								unsigned char b2 = (reg) & 255;

								unsigned char b4 = (adresiranje << 5) xor (reg << 1) xor high;

								string ss1;
								ostringstream t1;
								t1 << std::hex << (int)b4;
								string prvi;
								prvi = t1.str();
								if (prvi.size() == 1) {
									ss1 = "0";
								}

								ss1 += t1.str();


								list<SadrzajSekcija>::iterator i2;
								for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


									if ((i2->sekcija).compare(trenutnaSekcija) == 0) {

										i2->sadrzaj += ss1;

									}
								}


								locationCounter += 1;
							}//if regind
							else {
								if (op2.compare("regindpom") == 0) {
									string word = "";
									bool zagrada = false;
									for (auto x : sim)
									{

										if (x != '(' && !zagrada)
										{
											word = word + x;

										}
										else
										{
											zagrada = true;

										}

									} //for


									int high = 0;
									int adresiranje = 3;
									int reg;

									sim = sim.substr(word.size(), sim.size());

									sim = sim.substr(1, sim.size());

									sim = sim.substr(1, sim.size() - 2);

									string broj = sim.substr(1, 2);
									int br = std::stoi(broj);
									reg = br;


									unsigned char b1 = (adresiranje) & 255;
									unsigned char b2 = (reg) & 255;

									unsigned char b4 = (adresiranje << 5) xor (reg << 1) xor high;

									string ss1;
									ostringstream t1;
									t1 << std::hex << (int)b4;
									string prvi;
									prvi = t1.str();
									if (prvi.size() == 1) {
										ss1 = "0";
									}

									ss1 += t1.str();


									list<SadrzajSekcija>::iterator i2;
									for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


										if ((i2->sekcija).compare(trenutnaSekcija) == 0) {

											i2->sadrzaj += ss1;

										}
									}

									locationCounter += 1;

									memorijskoAdresiranje(word, trenutnaSekcija, locationCounter, brojacRbr, tabelaObracanjaUnapred, tabelaSimbola, tabelaRealokacije, listaSadrzajaSekcija);
									locationCounter += 2;


								}//if regindpom
								else {
									if (op2.compare("pcrel") == 0) {
										string word = "";
										bool zagrada = false;
										for (auto x : sim)
										{

											if (x != '(' && !zagrada)
											{
												word = word + x;

											}
											else
											{
												zagrada = true;

											}

										} //for


										int high = 0;
										int adresiranje = 3;
										int reg = 7;

										sim = sim.substr(word.size(), sim.size());



										unsigned char b1 = (adresiranje) & 255;
										unsigned char b2 = (reg) & 255;

										unsigned char b4 = (adresiranje << 5) xor (reg << 1) xor high;

										string ss1;
										ostringstream t1;
										t1 << std::hex << (int)b4;
										string prvi;
										prvi = t1.str();
										if (prvi.size() == 1) {
											ss1 = "0";
										}

										ss1 += t1.str();


										list<SadrzajSekcija>::iterator i2;
										for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


											if ((i2->sekcija).compare(trenutnaSekcija) == 0) {

												i2->sadrzaj += ss1;

											}
										}

										locationCounter += 1;

										pcrelativnoAdresiranje(word, trenutnaSekcija, locationCounter, brojacRbr, tabelaObracanjaUnapred, tabelaSimbola, tabelaRealokacije, listaSadrzajaSekcija);
										locationCounter += 2;

									}//if pc relativno
								}//else regindpom
							}//else regind
						}//else regdir
					}//else memdir


				} //if instrukcije sa jednim operandom i dst
				else {
					if ( tok.compare("push") == 0 || tok.compare("pushb") == 0 ) {
						//cout << "Instrukcija: " << tok << "\n";
						string op1 = odrediAdresiranje(sim);
						if (op1.compare("neposredno") == 0) {
							//neposredno adresiranje
							int adresiranje = 0;
							int reg = 0;

							unsigned char b1 = (adresiranje) & 255;
							unsigned char b2 = (reg) & 255;

							unsigned char b4 = (adresiranje << 5) xor (reg << 1) xor 0;

							string ss1;
							ostringstream t1;
							t1 << std::hex << (int)b4;
							string prvi;
							prvi = t1.str();
							if (prvi.size() == 1) {
								ss1 = "0";
							}

							ss1 += t1.str();


							list<SadrzajSekcija>::iterator i2;
							for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


								if ((i2->sekcija).compare(trenutnaSekcija) == 0) {

									i2->sadrzaj += ss1;

								}
							}

							locationCounter += 1;
							//zavrseno dodavanje prvog bajta adresiranja za neposredno

							if (velicina == 0) {
								//byte
								string rec1 = sim.substr(0, 1);

								//proveri da li je znak broj ili simbol
								bool hexadecimalan = false;
								string prvi_karakter = sim.substr(1, 2);
								sim = sim.substr(1, sim.size());

								if (prvi_karakter.compare("0x") == 0) {
									hexadecimalan = true;
								}


								if (sim.find_first_not_of("0123456789") != std::string::npos && !hexadecimalan) {
									//simbol

									list<Simbol>::iterator i;
									bool postojiuTabeli = false;
									for (i = tabelaSimbola.begin(); i != tabelaSimbola.end(); i++) {
										if (i->ime.compare(sim) == 0) {
											//ako vec postoji u tabeli simbola
											if (i->definisan) {
												//definisan
												if ((i->tip) == 'L') {
													//ako je local
													list<Simbol>::iterator i1;
													for (i1 = tabelaSimbola.begin(); i1 != tabelaSimbola.end(); i1++) {
														if ((i1->sekcija).compare(i->sekcija) == 0 && (i1->ime).compare(i->sekcija) == 0) {
															Relokacija rel = Relokacija(locationCounter, " R_386_32", i1->redniBr, trenutnaSekcija, sim, false);
															tabelaRealokacije.push_back(rel);


															bool dodajNulu = false;
															if (i->pomeraj <= 15) {
																dodajNulu = true;
															}

															unsigned char b1 = i->pomeraj & 255;
															if (i->pomeraj < -128 || i->pomeraj > 127) {
																cout << "Greska: literal u neposrednom adresiranju mora da bude jedan bajt, zato sto je instrukcija bajtovska!" << "\n";
																exit(1);
															}

															string ss;
															ostringstream t;
															t << std::hex << (int)b1;

															if (dodajNulu) {
																ss = "0";
															}
															ss += t.str();

															list<SadrzajSekcija>::iterator i2;
															for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


																if ((i2->sekcija).compare(trenutnaSekcija) == 0) {

																	i2->sadrzaj += ss;

																}
															}



														}//if postoji sekcija
													}//for sekcija
												}//if local
												else { //ako je global
													int redniBr = i->redniBr;
													Relokacija rel = Relokacija(locationCounter, " R_386_32", i->redniBr, trenutnaSekcija, "", false);
													tabelaRealokacije.push_back(rel);


													list<SadrzajSekcija>::iterator i2;
													for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


														if ((i2->sekcija).compare(trenutnaSekcija) == 0) {

															i2->sadrzaj += "00";

														}
													}
												}

											} //if definisan
											else {
												//postoji u tabeli ali nije definisan tabela obracanja unapred
												if ((i->tip) == 'L') {
													//dodaj novu bool vrednost u tabelu simbola da oznaci da treba da uradi i->pomeraj & 255; a ne samo da upise pomeraj

													ObracanjeUnapred obracanjeUna = ObracanjeUnapred(sim, locationCounter, 1, trenutnaSekcija, 'b', "");
													tabelaObracanjaUnapred.push_back(obracanjeUna);

													list<Simbol>::iterator i1;
													for (i1 = tabelaSimbola.begin(); i1 != tabelaSimbola.end(); i1++) {
														if ((i1->ime).compare(i->ime) == 0) {
															Relokacija rel = Relokacija(locationCounter, " R_386_32", i1->redniBr, trenutnaSekcija, sim, true);
															tabelaRealokacije.push_back(rel);


															list<SadrzajSekcija>::iterator i2;
															for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


																if ((i2->sekcija).compare(trenutnaSekcija) == 0) {

																	i2->sadrzaj += "00";

																}
															}


														}//if postoji sekcija
													}//for sekcija

												}
												else {
													//ako je global sve isto, ne dodajem u tabeli obracanja unapred
													int redniBr = i->redniBr;
													Relokacija rel = Relokacija(locationCounter, " R_386_32", i->redniBr, trenutnaSekcija, "", false);
													tabelaRealokacije.push_back(rel);

													list<SadrzajSekcija>::iterator i2;
													for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


														if ((i2->sekcija).compare(trenutnaSekcija) == 0) {

															i2->sadrzaj += "00";

														}
													}
												}

											} //else definisan
											postojiuTabeli = true;
										} // if da li postoji u tabeli simbola

									} //for

									if (!postojiuTabeli) {
										//ne postoji u tabeli, dodati i tabela obracanja unapred
										Simbol s = Simbol(sim, trenutnaSekcija, 0, NULL, 'L', brojacRbr, false, ' ');
										tabelaSimbola.push_back(s);
										brojacRbr++;

										ObracanjeUnapred obracanjeUna = ObracanjeUnapred(sim, locationCounter, 1, trenutnaSekcija, 'b', "");
										tabelaObracanjaUnapred.push_back(obracanjeUna);

										list<Simbol>::iterator i1;
										for (i1 = tabelaSimbola.begin(); i1 != tabelaSimbola.end(); i1++) {
											if ((i1->ime).compare(sim) == 0) {
												Relokacija rel = Relokacija(locationCounter, " R_386_32", i1->redniBr, trenutnaSekcija, sim, true);
												tabelaRealokacije.push_back(rel);


												list<SadrzajSekcija>::iterator i3;
												for (i3 = listaSadrzajaSekcija.begin(); i3 != listaSadrzajaSekcija.end(); i3++) {


													if ((i3->sekcija).compare(trenutnaSekcija) == 0) {

														i3->sadrzaj += "00";

													}
												}


											}//if postoji sekcija
										}//for sekcija


									}//if postoji



								}
								else {
									//broj
									long long n = std::stoll(sim, 0, 0);
									bool dodajNulu = false;
									if (n <= 15) {
										dodajNulu = true;
									}

									unsigned char b1 = n & 255;
									if (n < -128 || n > 127) {
										cout << "Greska: literal u neposrednom adresiranju mora da bude jedan bajt, zato sto je instrukcija bajtovska!" << "\n";
										exit(1);
									}

									string ss;
									ostringstream t;
									t << std::hex << (int)b1;

									if (dodajNulu) {
										ss = "0";
									}
									ss += t.str();



									list<SadrzajSekcija>::iterator i2;
									for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {
										//	cout << i2->sekcija << "\n";

										if ((i2->sekcija).compare(trenutnaSekcija) == 0) {
											//		cout << i2->sekcija<< " 1" <<  "\n";
											i2->sadrzaj += ss;

										}
									}

								}//else broj


								locationCounter += 1;
							} //if velicina = 0 byte
							else {
								if (velicina == 1) {

									neposrednoAdresiranje(sim, trenutnaSekcija, locationCounter, brojacRbr, tabelaObracanjaUnapred, tabelaSimbola, tabelaRealokacije, listaSadrzajaSekcija);
									locationCounter += 2;

								}//if vel = 1 word
							}//else velicina = 0 byte

						}//if neposredno
						else {
							if (op1.compare("memdir") == 0) {
								//neposredno adresiranje
								int adresiranje = 4;
								int reg = 0;

								unsigned char b1 = (adresiranje) & 255;
								unsigned char b2 = (reg) & 255;

								unsigned char b4 = (adresiranje << 5) xor (reg << 1) xor 0;

								string ss1;
								ostringstream t1;
								t1 << std::hex << (int)b4;
								string prvi;
								prvi = t1.str();
								if (prvi.size() == 1) {
									ss1 = "0";
								}

								ss1 += t1.str();


								list<SadrzajSekcija>::iterator i2;
								for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


									if ((i2->sekcija).compare(trenutnaSekcija) == 0) {

										i2->sadrzaj += ss1;

									}
								}

								locationCounter += 1;
								//zavrseno dodavanje prvog bajta adresiranja za neposredno


								memorijskoAdresiranje(sim, trenutnaSekcija, locationCounter, brojacRbr, tabelaObracanjaUnapred, tabelaSimbola, tabelaRealokacije, listaSadrzajaSekcija);
								locationCounter += 2;
							}//if memdir
							else {
								if (op1.compare("regdir") == 0) {
									//neposredno adresiranje
									int high = 0;
									int adresiranje = 1;
									int reg;
									sim = sim.substr(1, sim.size());
									if (sim.size() == 2) {
										if (velicina == 0) {
											cout << "Greska: instrukcija je byte, a operand je word!" << "\n";
											exit(1);
										}
										string broj = sim.substr(1, 2);
										int br = std::stoi(broj);
										reg = br;
									}
									else {
										if (sim.size() == 3) {
											if (velicina == 1) {
												cout << "Greska: instrukcija je word, a operand je byte!" << "\n";
												exit(1);
											}

											string broj = sim.substr(1, 2);
											int br = std::stoi(broj);
											reg = br;

											string hl = sim.substr(2, 3);
											if (hl.compare("h") == 0) {
												high = 1;
											}
											else {
												high = 0;
											}

										}
									}



									unsigned char b1 = (adresiranje) & 255;
									unsigned char b2 = (reg) & 255;

									unsigned char b4 = (adresiranje << 5) xor (reg << 1) xor high;

									string ss1;
									ostringstream t1;
									t1 << std::hex << (int)b4;
									string prvi;
									prvi = t1.str();
									if (prvi.size() == 1) {
										ss1 = "0";
									}

									ss1 += t1.str();


									list<SadrzajSekcija>::iterator i2;
									for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


										if ((i2->sekcija).compare(trenutnaSekcija) == 0) {

											i2->sadrzaj += ss1;

										}
									}

									locationCounter += 1;
									//zavrseno dodavanje prvog bajta adresiranja za neposredno
								}//if regdir
								else {
									if (op1.compare("regind") == 0) {
										//neposredno adresiranje
										int high = 0;
										int adresiranje = 2;
										int reg;

										sim = sim.substr(1, sim.size());

										sim = sim.substr(1, sim.size() - 2);

										string broj = sim.substr(1, 2);
										int br = std::stoi(broj);
										reg = br;


										unsigned char b1 = (adresiranje) & 255;
										unsigned char b2 = (reg) & 255;

										unsigned char b4 = (adresiranje << 5) xor (reg << 1) xor high;

										string ss1;
										ostringstream t1;
										t1 << std::hex << (int)b4;
										string prvi;
										prvi = t1.str();
										if (prvi.size() == 1) {
											ss1 = "0";
										}

										ss1 += t1.str();


										list<SadrzajSekcija>::iterator i2;
										for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


											if ((i2->sekcija).compare(trenutnaSekcija) == 0) {

												i2->sadrzaj += ss1;

											}
										}


										locationCounter += 1;
									}//if regind
									else {
										if (op1.compare("regindpom") == 0) {
											string word = "";
											bool zagrada = false;
											for (auto x : sim)
											{

												if (x != '(' && !zagrada)
												{
													word = word + x;

												}
												else
												{
													zagrada = true;

												}

											} //for


											int high = 0;
											int adresiranje = 3;
											int reg;

											sim = sim.substr(word.size(), sim.size());

											sim = sim.substr(1, sim.size());

											sim = sim.substr(1, sim.size() - 2);

											string broj = sim.substr(1, 2);
											int br = std::stoi(broj);
											reg = br;


											unsigned char b1 = (adresiranje) & 255;
											unsigned char b2 = (reg) & 255;

											unsigned char b4 = (adresiranje << 5) xor (reg << 1) xor high;

											string ss1;
											ostringstream t1;
											t1 << std::hex << (int)b4;
											string prvi;
											prvi = t1.str();
											if (prvi.size() == 1) {
												ss1 = "0";
											}

											ss1 += t1.str();


											list<SadrzajSekcija>::iterator i2;
											for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


												if ((i2->sekcija).compare(trenutnaSekcija) == 0) {

													i2->sadrzaj += ss1;

												}
											}

											locationCounter += 1;

											memorijskoAdresiranje(word, trenutnaSekcija, locationCounter, brojacRbr, tabelaObracanjaUnapred, tabelaSimbola, tabelaRealokacije, listaSadrzajaSekcija);
											locationCounter += 2;


										}//if regindpom
										else {
											if (op1.compare("pcrel") == 0) {
												string word = "";
												bool zagrada = false;
												for (auto x : sim)
												{

													if (x != '(' && !zagrada)
													{
														word = word + x;

													}
													else
													{
														zagrada = true;

													}

												} //for


												int high = 0;
												int adresiranje = 3;
												int reg = 7;

												sim = sim.substr(word.size(), sim.size());



												unsigned char b1 = (adresiranje) & 255;
												unsigned char b2 = (reg) & 255;

												unsigned char b4 = (adresiranje << 5) xor (reg << 1) xor high;

												string ss1;
												ostringstream t1;
												t1 << std::hex << (int)b4;
												string prvi;
												prvi = t1.str();
												if (prvi.size() == 1) {
													ss1 = "0";
												}

												ss1 += t1.str();


												list<SadrzajSekcija>::iterator i2;
												for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


													if ((i2->sekcija).compare(trenutnaSekcija) == 0) {

														i2->sadrzaj += ss1;

													}
												}

												locationCounter += 1;

												pcrelativnoAdresiranje(word, trenutnaSekcija, locationCounter, brojacRbr, tabelaObracanjaUnapred, tabelaSimbola, tabelaRealokacije, listaSadrzajaSekcija);
												locationCounter += 2;

											}//if pc relativno
										}//else regindpom
									}//else regind

								}//else regdir
							}//else memdir
						}//else neposredno
					} // if instr sa jednim operandom src
					else {
					if ( tok.compare("jmp") == 0 || tok.compare("jmpb") == 0 || tok.compare("jeq") == 0 || tok.compare("jeqb") == 0 
						|| tok.compare("jne") == 0 || tok.compare("jneb") == 0 	|| tok.compare("jgt") == 0 || tok.compare("jgtb") == 0 || tok.compare("call") == 0 || tok.compare("callb") == 0) {
						//cout << "Instrukcija: " << tok << "\n";
						string op1 = odrediAdresiranjeJump(sim);
						//cout << "Adresiranje skoka " << op1 << "\n";

						if (op1.compare("neposredno") == 0) {
							//neposredno adresiranje
							int adresiranje = 0;
							int reg = 0;

							unsigned char b1 = (adresiranje) & 255;
							unsigned char b2 = (reg) & 255;

							unsigned char b4 = (adresiranje << 5) xor (reg << 1) xor 0;

							string ss1;
							ostringstream t1;
							t1 << std::hex << (int)b4;
							string prvi;
							prvi = t1.str();
							if (prvi.size() == 1) {
								ss1 = "0";
							}

							ss1 += t1.str();


							list<SadrzajSekcija>::iterator i2;
							for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


								if ((i2->sekcija).compare(trenutnaSekcija) == 0) {

									i2->sadrzaj += ss1;

								}
							}

							locationCounter += 1;
							//zavrseno dodavanje prvog bajta adresiranja za neposredno

							if (velicina == 0) {
								//byte

								//proveri da li je znak broj ili simbol
								bool hexadecimalan = false;
								string prvi_karakter = sim.substr(0, 2);

								if (prvi_karakter.compare("0x") == 0) {
									hexadecimalan = true;
								}


								if (sim.find_first_not_of("0123456789") != std::string::npos && !hexadecimalan) {
									//simbol

									list<Simbol>::iterator i;
									bool postojiuTabeli = false;
									for (i = tabelaSimbola.begin(); i != tabelaSimbola.end(); i++) {
										if (i->ime.compare(sim) == 0) {
											//ako vec postoji u tabeli simbola
											if (i->definisan) {
												//definisan
												if ((i->tip) == 'L') {
													//ako je local
													list<Simbol>::iterator i1;
													for (i1 = tabelaSimbola.begin(); i1 != tabelaSimbola.end(); i1++) {
														if ((i1->sekcija).compare(i->sekcija) == 0 && (i1->ime).compare(i->sekcija) == 0) {
															Relokacija rel = Relokacija(locationCounter, " R_386_32", i1->redniBr, trenutnaSekcija, sim, false);
															tabelaRealokacije.push_back(rel);


															bool dodajNulu = false;
															if (i->pomeraj <= 15) {
																dodajNulu = true;
															}

															unsigned char b1 = i->pomeraj & 255;
															if (i->pomeraj < -128 || i->pomeraj > 127) {
																cout << "Greska: literal u neposrednom adresiranju mora da bude jedan bajt, zato sto je instrukcija bajtovska!" << "\n";
																exit(1);
															}

															string ss;
															ostringstream t;
															t << std::hex << (int)b1;

															if (dodajNulu) {
																ss = "0";
															}
															ss += t.str();

															list<SadrzajSekcija>::iterator i2;
															for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


																if ((i2->sekcija).compare(trenutnaSekcija) == 0) {

																	i2->sadrzaj += ss;

																}
															}



														}//if postoji sekcija
													}//for sekcija
												}//if local
												else { //ako je global
													int redniBr = i->redniBr;
													Relokacija rel = Relokacija(locationCounter, " R_386_32", i->redniBr, trenutnaSekcija, "", false);
													tabelaRealokacije.push_back(rel);


													list<SadrzajSekcija>::iterator i2;
													for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


														if ((i2->sekcija).compare(trenutnaSekcija) == 0) {

															i2->sadrzaj += "00";

														}
													}
												}

											} //if definisan
											else {
												//postoji u tabeli ali nije definisan tabela obracanja unapred
												if ((i->tip) == 'L') {
													//dodaj novu bool vrednost u tabelu simbola da oznaci da treba da uradi i->pomeraj & 255; a ne samo da upise pomeraj

													ObracanjeUnapred obracanjeUna = ObracanjeUnapred(sim, locationCounter, 1, trenutnaSekcija, 'b', "");
													tabelaObracanjaUnapred.push_back(obracanjeUna);

													list<Simbol>::iterator i1;
													for (i1 = tabelaSimbola.begin(); i1 != tabelaSimbola.end(); i1++) {
														if ((i1->ime).compare(i->ime) == 0) {
															Relokacija rel = Relokacija(locationCounter, " R_386_32", i1->redniBr, trenutnaSekcija, sim, true);
															tabelaRealokacije.push_back(rel);


															list<SadrzajSekcija>::iterator i2;
															for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


																if ((i2->sekcija).compare(trenutnaSekcija) == 0) {

																	i2->sadrzaj += "00";

																}
															}


														}//if postoji sekcija
													}//for sekcija

												}
												else {
													//ako je global sve isto, ne dodajem u tabeli obracanja unapred
													int redniBr = i->redniBr;
													Relokacija rel = Relokacija(locationCounter, " R_386_32", i->redniBr, trenutnaSekcija, "", false);
													tabelaRealokacije.push_back(rel);

													list<SadrzajSekcija>::iterator i2;
													for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


														if ((i2->sekcija).compare(trenutnaSekcija) == 0) {

															i2->sadrzaj += "00";

														}
													}
												}

											} //else definisan
											postojiuTabeli = true;
										} // if da li postoji u tabeli simbola

									} //for

									if (!postojiuTabeli) {
										//ne postoji u tabeli, dodati i tabela obracanja unapred
										Simbol s = Simbol(sim, trenutnaSekcija, 0, NULL, 'L', brojacRbr, false, ' ');
										tabelaSimbola.push_back(s);
										brojacRbr++;

										ObracanjeUnapred obracanjeUna = ObracanjeUnapred(sim, locationCounter, 1, trenutnaSekcija, 'b', "");
										tabelaObracanjaUnapred.push_back(obracanjeUna);

										list<Simbol>::iterator i1;
										for (i1 = tabelaSimbola.begin(); i1 != tabelaSimbola.end(); i1++) {
											if ((i1->ime).compare(sim) == 0) {
												Relokacija rel = Relokacija(locationCounter, " R_386_32", i1->redniBr, trenutnaSekcija, sim, true);
												tabelaRealokacije.push_back(rel);


												list<SadrzajSekcija>::iterator i3;
												for (i3 = listaSadrzajaSekcija.begin(); i3 != listaSadrzajaSekcija.end(); i3++) {


													if ((i3->sekcija).compare(trenutnaSekcija) == 0) {

														i3->sadrzaj += "00";

													}
												}


											}//if postoji sekcija
										}//for sekcija


									}//if postoji



								}
								else {
									//broj
									long long n = std::stoll(sim, 0, 0);
									bool dodajNulu = false;
									if (n <= 15) {
										dodajNulu = true;
									}

									unsigned char b1 = n & 255;
									if (n < -128 || n > 127) {
										cout << "Greska: literal u neposrednom adresiranju mora da bude jedan bajt, zato sto je instrukcija bajtovska!" << "\n";
										exit(1);
									}

									string ss;
									ostringstream t;
									t << std::hex << (int)b1;

									if (dodajNulu) {
										ss = "0";
									}
									ss += t.str();



									list<SadrzajSekcija>::iterator i2;
									for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {
										//	cout << i2->sekcija << "\n";

										if ((i2->sekcija).compare(trenutnaSekcija) == 0) {
											//		cout << i2->sekcija<< " 1" <<  "\n";
											i2->sadrzaj += ss;

										}
									}

								}//else broj


								locationCounter += 1;
							} //if velicina = 0 byte
							else {
								if (velicina == 1) {

									memorijskoAdresiranje(sim, trenutnaSekcija, locationCounter, brojacRbr, tabelaObracanjaUnapred, tabelaSimbola, tabelaRealokacije, listaSadrzajaSekcija);
									locationCounter += 2;

								}//if vel = 1 word
							}//else velicina = 0 byte

						}//if neposredno
						else {
							if (op1.compare("memdir") == 0) {
								//neposredno adresiranje
								int adresiranje = 4;
								int reg = 0;

								unsigned char b1 = (adresiranje) & 255;
								unsigned char b2 = (reg) & 255;

								unsigned char b4 = (adresiranje << 5) xor (reg << 1) xor 0;

								string ss1;
								ostringstream t1;
								t1 << std::hex << (int)b4;
								string prvi;
								prvi = t1.str();
								if (prvi.size() == 1) {
									ss1 = "0";
								}

								ss1 += t1.str();


								list<SadrzajSekcija>::iterator i2;
								for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


									if ((i2->sekcija).compare(trenutnaSekcija) == 0) {

										i2->sadrzaj += ss1;

									}
								}

								locationCounter += 1;
								//zavrseno dodavanje prvog bajta adresiranja za neposredno

								sim = sim.substr(1, sim.size());
								memorijskoAdresiranje(sim, trenutnaSekcija, locationCounter, brojacRbr, tabelaObracanjaUnapred, tabelaSimbola, tabelaRealokacije, listaSadrzajaSekcija);
								locationCounter += 2;
							}//if memdir
							else {
								if (op1.compare("regdir") == 0) {
									//neposredno adresiranje
									sim = sim.substr(1, sim.size());
									int high = 0;
									int adresiranje = 1;
									int reg;
									sim = sim.substr(1, sim.size());
									if (sim.size() == 2) {
										if (velicina == 0) {
											cout << "Greska: instrukcija je byte, a operand je word!" << "\n";
											exit(1);
										}
										string broj = sim.substr(1, 2);
										int br = std::stoi(broj);
										reg = br;
									}
									else {
										if (sim.size() == 3) {
											if (velicina == 1) {
												cout << "Greska: instrukcija je word, a operand je byte!" << "\n";
												exit(1);
											}

											string broj = sim.substr(1, 2);
											int br = std::stoi(broj);
											reg = br;

											string hl = sim.substr(2, 3);
											if (hl.compare("h") == 0) {
												high = 1;
											}
											else {
												high = 0;
											}

										}
									}



									unsigned char b1 = (adresiranje) & 255;
									unsigned char b2 = (reg) & 255;

									unsigned char b4 = (adresiranje << 5) xor (reg << 1) xor high;

									string ss1;
									ostringstream t1;
									t1 << std::hex << (int)b4;
									string prvi;
									prvi = t1.str();
									if (prvi.size() == 1) {
										ss1 = "0";
									}

									ss1 += t1.str();


									list<SadrzajSekcija>::iterator i2;
									for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


										if ((i2->sekcija).compare(trenutnaSekcija) == 0) {

											i2->sadrzaj += ss1;

										}
									}

									locationCounter += 1;
									//zavrseno dodavanje prvog bajta adresiranja za neposredno
								}//if regdir
								else {
									if (op1.compare("regind") == 0) {
										//neposredno adresiranje
										sim = sim.substr(1, sim.size());
										int high = 0;
										int adresiranje = 2;
										int reg;

										sim = sim.substr(1, sim.size());

										sim = sim.substr(1, sim.size() - 2);

										string broj = sim.substr(1, 2);
										int br = std::stoi(broj);
										reg = br;


										unsigned char b1 = (adresiranje) & 255;
										unsigned char b2 = (reg) & 255;

										unsigned char b4 = (adresiranje << 5) xor (reg << 1) xor high;

										string ss1;
										ostringstream t1;
										t1 << std::hex << (int)b4;
										string prvi;
										prvi = t1.str();
										if (prvi.size() == 1) {
											ss1 = "0";
										}

										ss1 += t1.str();


										list<SadrzajSekcija>::iterator i2;
										for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


											if ((i2->sekcija).compare(trenutnaSekcija) == 0) {

												i2->sadrzaj += ss1;

											}
										}


										locationCounter += 1;
									}//if regind
									else {
										if (op1.compare("regindpom") == 0) {
											sim = sim.substr(1, sim.size());

											string word = "";
											bool zagrada = false;
											for (auto x : sim)
											{

												if (x != '(' && !zagrada)
												{
													word = word + x;

												}
												else
												{
													zagrada = true;

												}

											} //for


											int high = 0;
											int adresiranje = 3;
											int reg;

											sim = sim.substr(word.size(), sim.size());

											sim = sim.substr(1, sim.size());

											sim = sim.substr(1, sim.size() - 2);

											string broj = sim.substr(1, 2);
											int br = std::stoi(broj);
											reg = br;


											unsigned char b1 = (adresiranje) & 255;
											unsigned char b2 = (reg) & 255;

											unsigned char b4 = (adresiranje << 5) xor (reg << 1) xor high;

											string ss1;
											ostringstream t1;
											t1 << std::hex << (int)b4;
											string prvi;
											prvi = t1.str();
											if (prvi.size() == 1) {
												ss1 = "0";
											}

											ss1 += t1.str();


											list<SadrzajSekcija>::iterator i2;
											for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


												if ((i2->sekcija).compare(trenutnaSekcija) == 0) {

													i2->sadrzaj += ss1;

												}
											}

											locationCounter += 1;

											memorijskoAdresiranje(word, trenutnaSekcija, locationCounter, brojacRbr, tabelaObracanjaUnapred, tabelaSimbola, tabelaRealokacije, listaSadrzajaSekcija);
											locationCounter += 2;


										}//if regindpom
										else {
											if (op1.compare("pcrel") == 0) {

												sim = sim.substr(1, sim.size());

												string word = "";
												bool zagrada = false;
												for (auto x : sim)
												{

													if (x != '(' && !zagrada)
													{
														word = word + x;

													}
													else
													{
														zagrada = true;

													}

												} //for


												int high = 0;
												int adresiranje = 3;
												int reg = 7;

												sim = sim.substr(word.size(), sim.size());



												unsigned char b1 = (adresiranje) & 255;
												unsigned char b2 = (reg) & 255;

												unsigned char b4 = (adresiranje << 5) xor (reg << 1) xor high;

												string ss1;
												ostringstream t1;
												t1 << std::hex << (int)b4;
												string prvi;
												prvi = t1.str();
												if (prvi.size() == 1) {
													ss1 = "0";
												}

												ss1 += t1.str();


												list<SadrzajSekcija>::iterator i2;
												for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


													if ((i2->sekcija).compare(trenutnaSekcija) == 0) {

														i2->sadrzaj += ss1;

													}
												}

												locationCounter += 1;

												pcrelativnoAdresiranje(word, trenutnaSekcija, locationCounter, brojacRbr, tabelaObracanjaUnapred, tabelaSimbola, tabelaRealokacije, listaSadrzajaSekcija);
												locationCounter += 2;

											}//if pc relativno
										}//else regindpom
									}//else regind

								}//else regdir
							}//else memdir
						}//else neposredno

					} //if instrukcije jmp
					
					} //else instr sa jednim operandom src
					} //else instr sa jednim operandom dst
				} //else instr sa 2 operanda

				}//if nije instrukcija sa jednim operandom

				}//if instr
				else {
					if (!lab1) {
						cout << "Greska simbol: " << tok << " ne postoji!" << "\n";
						exit(1);
					}
				}
			}
		

			}
		
		

	} // while


	//razresavanje simbola kod equ

	list<NerazreseniSimboli>::iterator ik;
	for (ik = tabelaNerazresenihSimbola.begin(); ik != tabelaNerazresenihSimbola.end(); ik++) {
		

			list<Simbol>::iterator ii;
			int pom;
			bool definisan = false;
			for (ii = tabelaSimbola.begin(); ii != tabelaSimbola.end(); ii++) {
				if ((ii->ime).compare(ik->equsimbol) == 0 && ii->definisan) {
					pom = ii->pomeraj;
					definisan = true;
				}
				
			} // for tabela simbola
			if (!definisan) {
				cout << "Greska: simbol: " << ik->equsimbol << "nije definisan!" << "\n";
				exit(1);
			}

			list<Simbol>::iterator i2;
			string ss = "";
			for (i2 = tabelaSimbola.begin(); i2 != tabelaSimbola.end(); i2++) {
				if ((i2->ime).compare(ik->ime) == 0) {

					unsigned char b1 = pom & 255;
					if (ik->velicina == 2) {
						i2->pomeraj = (int)b1;
					}
					else {
						if (ik->velicina == 0) {
							i2->pomeraj = i2->pomeraj + (int)b1;
						}
						else {
							if (ik->velicina == 1) {
								i2->pomeraj = i2->pomeraj - (int)b1;
							}
						}
					}
				}


			} // for tabela simbola
		
	}//nerazresenih simbola
	

	//	razresavanjeTabeleObracanja(tabelaSimbola, tabelaObracanjaUnapred, listaSadrzajaSekcija);

	list<ObracanjeUnapred>::iterator i;
	for (i = tabelaObracanjaUnapred.begin(); i != tabelaObracanjaUnapred.end(); i++) {
		

		if (i->tip == 'b') {
			//sredi byte

			list<Simbol>::iterator ii;
			string ss = "";
			for (ii = tabelaSimbola.begin(); ii != tabelaSimbola.end(); ii++) {
				if ((ii->ime).compare(i->ime) == 0) {
					bool dodajNulu = false;
					if (ii->pomeraj <= 15) {
						dodajNulu = true;
					}

					unsigned char b1 = ii->pomeraj & 255;
					if (ii->pomeraj < -128 || ii->pomeraj > 127) {
						cout << "Greska: u direktivi .byte literal nije odgovarajuce sirine!" << "\n";
						exit(1);
					}


					ostringstream t;
					t << std::hex << (int)b1;
					if (dodajNulu) {
						ss = "0";
					}
					ss += t.str();
				}
			} // for tabela simbola

			list<SadrzajSekcija>::iterator i2;
			for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


				if ((i2->sekcija).compare(i->sekcija) == 0) {
					int i1 = 0;
					SadrzajSekcija sadrzajSek = *i2;
					for (std::string::iterator it = sadrzajSek.sadrzaj.begin(); it != sadrzajSek.sadrzaj.end(); ++it) {
						if (i1 % 2 == 0) {
							//cout << i->path << " " << i1 / 2 << "\n";
							if (i1 / 2 == i->path) {
							//	cout << "Ok " << i2->sadrzaj << "\n";

								i2->sadrzaj.replace(i1, 2 * i->velicina, ss); //4 = 2*broj baajtova koje treba izmeniti
							//	cout << "Ok1 " << i2->sadrzaj << "\n";
							}

						}
						i1++;
					} //for sadrzaj sekcije

				}
			}//for
		} // if b
		else {
			if (i->tip == 'w') {

				list<Simbol>::iterator ii;
				string ss = "";
				for (ii = tabelaSimbola.begin(); ii != tabelaSimbola.end(); ii++) {
					if ((ii->ime).compare(i->ime) == 0) {
						unsigned char b1 = ii->pomeraj & 255;
						unsigned char b2 = (ii->pomeraj >> 8) & 255;
						if (ii->pomeraj < -32768 || ii->pomeraj > 32767) {
							cout << "Greska: u direktivi .word literal nije odgovarajuce sirine!" << "\n";
							exit(1);
						}

						
						ostringstream t;
						t << std::hex << (int)b1;
						/*		if (dodajNulu) {
									ss = "0";
								} */
						string prvi;
						prvi = t.str();
						if (prvi.size() == 1) {
							ss = "0";
						}
						ss += t.str();
						string drugi;
						ostringstream t1;
						t1 << std::hex << (int)b2;
						drugi = t1.str();
						if (drugi.size() == 1) {
							ss += "0";
						}
						ss += t1.str();
					
					}


				} // for tabela simbola

				list<SadrzajSekcija>::iterator i2;
				for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


					if ((i2->sekcija).compare(i->sekcija) == 0) {
						int i1 = 0;
						SadrzajSekcija sadrzajSek = *i2;
						for (std::string::iterator it = sadrzajSek.sadrzaj.begin(); it != sadrzajSek.sadrzaj.end(); ++it) {
							if (i1 % 2 == 0) {
								//cout << i->path << " " << i1 / 2 << "\n";
								if (i1 / 2 == i->path) {
								//	cout << "Ok " << i2->sadrzaj << "\n";

									i2->sadrzaj.replace(i1, 2 * i->velicina, ss); //4 = 2*broj baajtova koje treba izmeniti
								//	cout << "Ok1 " << i2->sadrzaj << "\n";
								}

							}
							i1++;
						} //for sadrzaj sekcije

					}
				}//for
			}
			else {
				if (i->tip == 'r') {

					list<Simbol>::iterator ii;
					string ss = "";
					for (ii = tabelaSimbola.begin(); ii != tabelaSimbola.end(); ii++) {
						if ((ii->ime).compare(i->ime) == 0) {

							int pom = ii->pomeraj - 2;

							unsigned char b1 = pom & 255;
							unsigned char b2 = (pom >> 8) & 255;
							if (pom < -32768 || pom > 32767) {
								cout << "Greska:  literal nije odgovarajuce sirine kod neposrednog adresiranja!" << "\n";
								exit(1);
							}
						

							ostringstream t;
							t << std::hex << (int)b1;
							/*		if (dodajNulu) {
										ss = "0";
									} */
							string prvi;
							prvi = t.str();
							if (prvi.size() == 1) {
								ss = "0";
							}
							ss += t.str();
							string drugi;
							ostringstream t1;
							t1 << std::hex << (int)b2;
							drugi = t1.str();
							if (drugi.size() == 1) {
								ss += "0";
							}
							ss += t1.str();

						}


					} // for tabela simbola

					list<SadrzajSekcija>::iterator i2;
					for (i2 = listaSadrzajaSekcija.begin(); i2 != listaSadrzajaSekcija.end(); i2++) {


						if ((i2->sekcija).compare(i->sekcija) == 0) {
							int i1 = 0;
							SadrzajSekcija sadrzajSek = *i2;
							for (std::string::iterator it = sadrzajSek.sadrzaj.begin(); it != sadrzajSek.sadrzaj.end(); ++it) {
								if (i1 % 2 == 0) {
									//cout << i->path << " " << i1 / 2 << "\n";
									if (i1 / 2 == i->path) {
									//	cout << "Ok " << i2->sadrzaj << "\n";

										i2->sadrzaj.replace(i1, 2 * i->velicina, ss); //4 = 2*broj baajtova koje treba izmeniti
									//	cout << "Ok1 " << i2->sadrzaj << "\n";
									}

								}
								i1++;
							} //for sadrzaj sekcije

						}
					}//for
				}
			}// else tip = w
		
		} // else tip = b
	}//for za tabelu Obracanja unapred




	//tabela realokacija 
	list<Relokacija>::iterator i2;
	for (i2 = tabelaRealokacije.begin(); i2 != tabelaRealokacije.end(); i2++) {
		if(i2->popravi) {

			list<Simbol>::iterator i1;
			int redniBr;
			for (i1 = tabelaSimbola.begin(); i1 != tabelaSimbola.end(); i1++) {
				if (i1->redniBr == i2->vrednost) {

					list<Simbol>::iterator i;

					for (i = tabelaSimbola.begin(); i != tabelaSimbola.end(); i++) {
						if ((i->ime).compare(i1->sekcija) == 0 && i->sekcija.compare(i1->sekcija) == 0) {
							redniBr = i->redniBr;
						}
					}//for sekciju
				}//if redniBroj
			}//for simbol
		

			
			i2->vrednost = redniBr;
			i2->popravi = false;
		
	
		} //if popravi
	}//for realokacija

	int nrel = tabelaRealokacije.size();
	list<Relokacija> tabRel2;
	tabRel2 = tabelaRealokacije;
	list<Relokacija>::iterator im;
	for (im = tabRel2.begin(); im != tabRel2.end(); im++) {

		nrel--;
		Relokacija relok =tabelaRealokacije.front();
		tabelaRealokacije.erase(tabelaRealokacije.begin());

		list<Simbol>::iterator i1;
		bool brisati = false;
		for (i1 = tabelaSimbola.begin(); i1 != tabelaSimbola.end(); i1++) {
			if (relok.ime.compare(i1->ime) == 0 && i1->externglobal == 'e') {
			
				brisati = true;
			}// if
		}//for tabela simbola

		if (!brisati) {
			tabelaRealokacije.push_back(relok);
		}

	}//for tabela


	list<Relokacija>::iterator it;
	for (it = tabelaRealokacije.begin(); it != tabelaRealokacije.end(); it++) {
		it->popravi = false;
	}


	list<Simbol>::iterator i5;
	list<Simbol> tabelaSim = tabelaSimbola;
	int cnt = 0;
	for (i5 = tabelaSimbola.begin(); i5 != tabelaSimbola.end(); i5++) {
		if (i5->ime.compare(i5->sekcija) == 0) {
			list<Relokacija>::iterator i7;
			for (i7 = tabelaRealokacije.begin(); i7 != tabelaRealokacije.end(); i7++) {
				if (i7->vrednost == i5->redniBr && !i7->popravi) {
					i7->vrednost = cnt;
					i7->popravi = true;
				}
			}
			i5->redniBr = cnt;
			cnt++;
		}
	}
	list<Simbol>::iterator i4;
	for (i4 = tabelaSim.begin(); i4 != tabelaSim.end(); i4++) {
		if (i4->ime.compare(i4->sekcija) != 0) {
			list<Relokacija>::iterator i7;
			for (i7 = tabelaRealokacije.begin(); i7 != tabelaRealokacije.end(); i7++) {
				if (i7->vrednost == i4->redniBr && !i7->popravi) {
					i7->vrednost = cnt;
					i7->popravi = true;
				}
			}
			list<Simbol>::iterator im;
			for (im = tabelaSimbola.begin(); im != tabelaSimbola.end(); im++) {
				if (i4->ime.compare(im->ime) == 0) {
					im->redniBr = cnt;
				}
			}
			cnt++;
		}
	} 

	obradaDirGlobal(tabelaSimbola);
	obradaDirExtern(tabelaSimbola);

//	ispisTabelaNerazresenihSimbola(izlaz, tabelaNerazresenihSimbola);

//	ispisTabelaObracanjaUnapred(izlaz, tabelaObracanjaUnapred);
	ispisTabelaRealokacije(izlaz, tabelaRealokacije);

	ispisSadrzajaSekcija(izlaz, listaSadrzajaSekcija);

	//da li postoji u tabeli ako postoji

	ispisTabeleSimbola(izlaz, tabelaSimbola);

	return 0;
}
