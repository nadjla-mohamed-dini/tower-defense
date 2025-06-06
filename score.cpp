#include "score.h"
#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream fichier("C:/Users/fatyl/CLionProjects/untitled/tower defence/socretower.txt");

    if (!fichier) {
        std::cerr << "Erreur : impossible d'ouvrir le fichier scoretower.txt" << std::endl;
        return 1;
    }

    int score;
    int compteur = 1;

    std::cout<<"Liste des scores: " <<std::endl;

    while (fichier>>score) {
        std::cout<<score<<compteur<<":"<<score<<std::endl;
        compteur++;
    }

    if (fichier.bad()) {
        std::cerr<<"Erreur le lecture du fichier."<<std::endl;
        return 1;
    }
    return 0;

}
