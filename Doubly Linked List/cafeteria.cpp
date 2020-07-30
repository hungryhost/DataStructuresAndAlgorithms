#include <iostream>
#include "dish.h"
#include <math.h>
#include "linkedlist.h"

tDish::tDish(std::string m_name, double m_weight, double m_fats, double m_proteins, double m_carbs, double m_acids,
           double m_cellulose)
{
    if (m_name[0] != NULL)
        this->name = m_name;
    else
        this->name = "Dish";
    if (m_weight > 0)
    {
        this->weight = m_weight;
        }
    else{
        this->weight = 100;
    }
    if (m_fats > 0 && m_fats < 100)
    {
        this->fats = m_fats;
        }
    else{
        this->fats = 1;
    }
    if (m_proteins > 0 && m_proteins < 100)
    {
        this->proteins = m_proteins;
        }
    else {
        this->proteins = 1;
    }
    if (m_carbs > 0 && m_carbs < 100)
    {
        this->carbs = m_carbs;
    }
        else {
            this->carbs = 1;
    }
    if (m_acids > 0 && m_acids < 100)
    {
        this->acids = m_acids;
        }
        else {
            this->acids = 1;
    }

    if (m_cellulose > 0 && m_cellulose < 100)
    {
        this->cellulose = m_cellulose;
    }
        else
        this->cellulose = 1;
    this-> tenergy = (weight/100)*(fats*(9.29)+proteins*(4.1)+carbs*(4.1)+acids*(2.2)+cellulose*(1.9));
    this->tenergy = round(this->tenergy*1000)/1000;
}

tDish::tDish(const tDish &other){
    this->name = other.name;
    this->weight = other.weight;
    this->fats = other.fats;
    this->proteins = other.proteins;
    this->carbs = other.carbs;
    this->acids = other.acids;
    this->cellulose = other.cellulose;
    this->tenergy = other.tenergy;

}
Dish::Dish(){this->n_name = "Dish";
                this->weight = 100;
                this->fats = 1;
                this->proteins = 1;
                this->carbs = 1;
                this->acids = 1;
                this->cellulose = 1;
                this->energy = (weight/100)*(fats*(9.29)+proteins*(4.1)+carbs*(4.1)+acids*(2.2)+cellulose*(1.9));
                this->energy = round(this->energy*1000)/1000;
                this->type = 1;}
tDish::tDish(){this->name = "Dish";
                this->weight = 100;
                this->fats = 1;
                this->proteins = 1;
                this->carbs = 1;
                this->acids = 1;
                this->cellulose = 1;
                this->tenergy = (weight/100)*(fats*(9.29)+proteins*(4.1)+carbs*(4.1)+acids*(2.2)+cellulose*(1.9));
                this->tenergy = round(this->tenergy*1000)/1000;
                }
void tDish::changeweight(double n_weight){
    if (n_weight > 0)
    {
       this->weight = n_weight;
    }
}

void tDish::changefats(double n_fats){
    if (n_fats >= 0 && n_fats < 100)
    {
        this->fats = n_fats;
    }
}
void tDish::changeacids(double n_acids){
    if (n_acids >= 0 && n_acids < 100)
    {
        this->acids = n_acids;
    }
}

void tDish::changecarbs(double n_carbs){
    if (n_carbs >= 0 && n_carbs < 100)
    {
        this->carbs = n_carbs;
    }
}
void tDish::changeprot(double n_proteins){
    if (n_proteins >= 0 && n_proteins < 100)
    {
        this->proteins = n_proteins;
    }
}
void tDish::changecell(double n_cellulose){
    if (n_cellulose >= 0 && n_cellulose < 100)
        {
        this->cellulose = n_cellulose;
        }
}
void tDish::changename(std::string m_name){
    if (m_name[0] != NULL)
        this->name = m_name;
}
std::string tDish::retname() const{
    return name;
}
double tDish::retweight() const{
    return weight;
}
double tDish::retfats() const{
    return fats;
}
double tDish::retproteins() const{
    return proteins;
}
double tDish::retcarbs() const{
    return carbs;
}
double tDish::retacids() const{
    return acids;
}
double tDish::retcellulose() const{
    return cellulose;
}
double tDish::retenergy() const{
    return tenergy;
}

