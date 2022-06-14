/*
	Name: Rediat Shamsu
	Email: rbshamsu@crimson.ua.edu
*/
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <unordered_map>
#include <vector>
#include <chrono>
bool inLibrary(std::string item, std::unordered_map<std::string,std::vector<std::string>> Library){
	if(Library.find(item)==Library.end()){
		return false;
	}
	return true;
};
bool isMovie(std::string movie, std::unordered_map<std::string,std::vector<std::string>> movieLibrary){
	return inLibrary(movie, movieLibrary);
};
bool isActor(std::string actor, std::unordered_map<std::string,std::vector<std::string>> actorLibrary){
	return inLibrary(actor, actorLibrary);
};	
void searchByActor(std::string actorName, std::unordered_map<std::string,std::vector<std::string>> actorLibraryName){
	if(!isActor(actorName, actorLibraryName)){
			std::cout << "Actor : " <<actorName << " not found. Ensure spelling is correct and the name is formatted as Last Name, First Name."<< std::endl;
		}else{
			std::vector<std::string> actorMovies = actorLibraryName.at(actorName);
			std::cout << actorName<<" has worked in the following movies: "<<std::endl;
			for(int i = 0; i < actorMovies.size(); i++){
				std::cout<< actorMovies.at(i)<<std::endl;
			}
		}
		return;
	};
void searchByMovie(std::string movieName, std::unordered_map<std::string,std::vector<std::string>> movieLibraryName){
	if(!isMovie(movieName, movieLibraryName)){
			std::cout << "Movie : " <<movieName << " not found. Ensure spelling is correct."<< std::endl;
		}else{
			std::vector<std::string> movieActors = movieLibraryName.at(movieName);
			std::cout << movieName<<" has the following actors in it: "<<std::endl;
			for(int i = 0; i < movieActors.size(); i++){
				std::cout<< movieActors.at(i)<<std::endl;
			}
		}
		return;
	};
void executeQueries(std::vector<std::string> queries, std::unordered_map<std::string,std::vector<std::string>> movieLibrary,std::unordered_map<std::string,std::vector<std::string>> actorLibrary){
	std::cout << "Executing Queries..."<<std::endl;
	for(int i = 0; i < queries.size(); i++){
		if(isMovie(queries.at(i), movieLibrary)){
			searchByMovie(queries.at(i), movieLibrary);
		}
		else if(isActor(queries.at(i), actorLibrary)){
			searchByActor(queries.at(i), actorLibrary);
		}else{
			std::cout << "Query: "<< queries.at(i) <<" is neither a movie nor an actor in the Library. Ensure spelling and formatting is correct.\n Format for actor is Last Name, First Name. And, note that the Library contains the name for actors not characters in a movie."<<std::endl;
		}
	}
	return;
};
int main(int argc, char *argv[]) {
	std::unordered_map<std::string,std::vector<std::string>> movieLibrary,actorLibrary;
	std::vector<std::string> queryVector;
	auto createStart = std::chrono::steady_clock::now();
	int i = 0;
	// check for correct command-line arguments
	if (argc != 3) {
	   std::cout << "Usage: " << argv[0] << " <db file> <query file>" << std::endl;
	   std::exit(-1);
	}

	std::string line, name;
	std::regex delim("/");
	std::ifstream dbfile(argv[1]);
	if (!dbfile.is_open()) {
	   std::cout << "Unable to open file: " << argv[1] << std::endl;
	   std::exit(-1);
	}
	std::string movie;
	std::string actor;
	//std::cout << "***Reading db file " << argv[1] << "***" << std::endl;
	while (std::getline(dbfile, line)) {
	   // parse each line for tokens delimited by "/"
	   auto begin = std::sregex_token_iterator(line.begin(), line.end(), delim, -1);
	   auto end = std::sregex_token_iterator();
	   //std::cout << "***Line " << ++i << " ***" << std::endl;
	   movie = *begin;
	   std::vector<std::string> actorsInMovie;	   
	   //std::cout << "Movie:\t" << *begin << std::endl;
	   ++begin;
	   //std::cout << "Actors: " << std::endl;
	   for (std::sregex_token_iterator word = begin; word != end; ++word) {
		actor = (*word);
		//std::cout << "\t" << *word<<std::endl;
		actorsInMovie.push_back(actor);
		if(actorLibrary.count(actor)!=0){
		std::vector<std::string>actorMovieList = actorLibrary.at(actor);
		actorMovieList.push_back(movie);
		}else{
			std::vector<std::string>actorMovieList;
			actorMovieList.push_back(movie);
			std::pair<std::string,std::vector<std::string>> actorMovieEntry(actor, actorMovieList);
			actorLibrary.insert(actorMovieEntry);
		}
	   }
	   std::pair<std::string,std::vector<std::string>>movieEntry(movie,actorsInMovie);
	   movieLibrary.insert(movieEntry);
	}
	auto createEnd = std::chrono::steady_clock::now();
	dbfile.close();
	//std::cout << "***Done reading db file " << argv[1] << "***" << std::endl;

	std::ifstream queryfile(argv[2]);
	if (!queryfile.is_open()) {
	   std::cout << "Unable to open file: " << argv[2] << std::endl;
	   std::exit(-1);
	}

	//std::cout << "***Reading query file " << argv[2] << "***" << std::endl;
	while (std::getline(queryfile, name)) {
	   //std::cout << name << std::endl;
	   queryVector.push_back(name);
	}
	queryfile.close();
	//std::cout << "***Done reading query file " << argv[2] << "***" << std::endl;
	auto searchStart = std::chrono::steady_clock::now();
	executeQueries(queryVector, movieLibrary, actorLibrary);
	auto searchEnd = std::chrono::steady_clock::now();
	std::chrono::duration<double> createDuration = createEnd - createStart;
	std::chrono::duration<double> searchDuration = searchEnd - searchStart;
	std::cout << "Creation Time is "<< createDuration.count() <<"s." << std::endl;
	std::cout << "Search Time is "<< searchDuration.count() <<"s." << std::endl;	
	std::cout << "Number of movies is " << movieLibrary.size() << " movies." <<std::endl;
	std::cout << "Number of actors is " << actorLibrary.size() << " actors." <<std::endl;
	return 0;
}

