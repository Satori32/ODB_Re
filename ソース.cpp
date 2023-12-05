#include <iostream>
#include <map>
#include <vector>
#include <memory>
#include <string>
#include <cstdint>
#include <algorithm>
#include <ctime>

class ObjectDatabase {
public:
	struct Parson{
		std::string ID;
		std::map < std::string, std::string> P;
		
		bool Add(const std::string& ID, const std::string& D) {
			P[ID] = D;
			return true;
		}
		bool Erase(const std::string& ID) {
			P.erase(ID);
			return true;
		}
		std::map < std::string, std::string>::iterator begin() {
			return P.begin();
		}
		std::map < std::string, std::string>::iterator end() {
			return P.end();
		}

	};
	typedef std::shared_ptr<Parson> SharedParson;
	struct Relation
	{
		struct Arrow
		{
			std::shared_ptr<Parson> To;
			std::intmax_t Weight = 0;
			std::vector<std::string> Origin;
			bool SetOrigin(const std::string& In) {
				Origin.push_back(In);
			}
			bool SetWeight(std::intmax_t In) {
				Weight = In;
			}

		};
		std::vector<Arrow> R;
		bool PushArrow(std::shared_ptr<Parson> P, std::intmax_t W) {
			R.push_back({ P,W });
			return true;
		}

		bool PopArrow(Arrow A) {
			for (auto i = R.begin(); i != R.end(); i++) {
				if (i->To == A.To) {
					R.erase(i);
					return true;
				}
			}
			return false;
		}

		std::vector<Arrow>::iterator begin() {
			return R.begin();
		}
		std::vector<Arrow>::iterator end() {
			return R.end();
		}
	};

	struct Info
	{
		std::string Info;
		std::map < std::string, std::string > Data;
	};
	enum class User : std::intmax_t
	{
		Initialize,
		A,
		B,
		C,
		Process,
		Destruct,

	
	};
	enum class Server// : std::intmax_t
	{

		Initialize,
		Create,
		Seach,
		A,
		B,
		C,
		Process,
		Destruct,
		
	};		
	template<class E>
	struct Event{

		/**/
		typedef Event<E> DeclEvent;
		/**/
		struct EventData {
			E Event;
			std::string Tag;
			std::time_t Time;
		};

		std::vector<EventData> Events;
		bool Fire(E Ev, std::string Tag) {
			std::time_t T{};
			std::ctime(&T);
			EventData EV{ Ev,Tag, T };
		
			Events.push_back(EV);
			return true;
		}

	};

	struct ParsonalData//what are you need the one page.
	{
		std::shared_ptr<Parson> P;
		std::map<std::string, Info> Info;
		Relation R;	
		Event<User> E;
	};
	
	typedef std::shared_ptr<ParsonalData> SharedParsonData;

	bool New(const std::string& ID) {
		SharedParson P = std::make_shared<Parson>();
		P->ID = ID;

		//E.Fire(ObjectDatabase::Event<Server>::DeclEvent::Create, "Tukurimaita");//why cant Pass?
		return this->Push(P);
	}

	bool Push(std::shared_ptr<Parson> P) {
		for (auto i = D.begin(); i != D.end(); i++) {
			if (i->get()->P->ID == P->ID) {
				return false;
			}
		}

	//	E.Fire(ObjectDatabase::Event<Server>::DeclEvent::DeclEvent::Search, "MiTsuketa!!!");//why cant Pass?
		
		//SharedParsonData X{ P,{}, {} };//where is to memorylize? ah null? bakayarou!

		//SharedParsonData Z = std::make_shared<ParsonalData>(P, Info(),Relation(),Event());
		SharedParsonData Z = std::make_shared<ParsonalData>();
		Z->P = P;
		D.push_back(Z);

		return true;
	}
	bool Erase(std::shared_ptr<Parson> P) {
		for (auto i = D.begin(); i != D.end(); i++) {
			if (P->ID == i->get()->P->ID) {
				D.erase(i);
				return true;
			}
		}

		return false;
	}


	SharedParsonData Find(std::string ID) {
		for (auto& o : D) {
			if (o->P->ID == ID) { return o; }
		}
		return nullptr;
	}
	SharedParsonData Find(SharedParson P) {
		for (auto& o : D) {
			if (o->P->ID == P->ID) { return o; }
		}
		return nullptr;
	}

	std::vector<SharedParsonData>::iterator begin() {
		return D.begin();
	}

	std::vector<SharedParsonData>::iterator end() {
		return D.end();
	}
	SharedParsonData& operator[](const std::size_t& In) {
		return D[In];
	}

protected:

	std::vector<SharedParsonData> D;
	Event<Server> E;
};

int main() {
	ObjectDatabase ODB;
	ObjectDatabase::SharedParson P=std::make_shared<ObjectDatabase::Parson>();
	ObjectDatabase::SharedParsonData OSP = std::make_shared<ObjectDatabase::ParsonalData>();

	P->Add("Hoge", "X");
	P->Add("hage", "baru");	

	for (auto& o : *P) {
		std::cout << o.first << ':' << o.second << std::endl;
	}

	return 0;
}