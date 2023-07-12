#include <iostream>
#include <list>
#include <random>
#include <tuple>
#include <cmath>

#define INF 2147483647

using namespace std;

int N = 10000;

float randa() {
	float r = rand();
	float x = (r/RAND_MAX)*2.0 - 1.0;
	return x;
}

float media(std::list<float> x) {
	float s = 0; 
	for(auto xi : x) {
		s += xi; 
	}
	return s/x.size();
}

float var(std::list<float> x) {
	float s = 0;
	float m = media(x); 
	for(auto xi : x) {
		s += (xi - m)*(xi - m);
	}
	return s/x.size();
}

class Particle {
public:
    std::list<float> x;
    std::list<float> v;
    float J = 0;
    Particle* Best; 
    void setX(std::list<float> x) {
        this->x = x;
    }
    void setV(std::list<float> v) {
        this->v = v;
    }
    void setJ(float J) {
        this->J = J;
    }
    std::list<float> getX() {
        return this->x;
    }
    std::list<float> getV() {
        return this->v;
    }
    float getJ() {
        return this->J;
    }
    Particle(){}
    Particle(Particle& p) {
	    this->x = p.getX();
	    this->v = p.getV();
	    this->J = p.getJ();
    }
    ~Particle() {
    	delete Best; 
    }
    void toString() {
        std::cout << "X:: ";
        for (auto it_x = x.begin(); it_x != x.end(); it_x++) {
            std::cout << std::abs(*it_x) << " ";
        }
        std::cout << ", J::" << getJ() << std::endl;
    }
};

// função para gerar números aleatórios uniformes entre xMin e xMax
std::list<float> unifrnd(float xMin, float xMax, int n) {
    std::list<float> x;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(xMin, xMax);
    for (int i = 0; i < n; i++) {
        x.push_back(dis(gen));
    }
    return x;
}
// função custo 
float funObj(std::list<float> x, std::list<float> prices, float value) {
    float J = 0; 
    float error = 0; 
    auto it_x = x.begin();
    auto it_p = prices.begin();
    while(it_x != x.end() && it_p != prices.end()) {
        J += std::abs((*it_x)) * std::abs((*it_p));
        ++it_x;
        ++it_p;
    }
    auto it = x.begin();
    auto x1 = *it;
    std::advance(it, 1); 
    auto x2 = *it; 
    std::advance(it, 1); 
    auto x3 = *it; 
    
    float e1 = (x1) / (x2) - (200.0/395.0); 
    float e2 = (x1) / (x3) - (200.0/380.0); 
    
    error = J - value; 
    J = error * error / 2.0 + 100 * e1 * e1 + 100 * e2 * e2; 
    return J;
}

void InitP(std::list<Particle>& P, Particle& Gbest, std::list<float> prices, float value) {
    float xMax = 100;
    float xMin = -100;
    float vMax = 0;	
    for (auto& p : P) {
        p.setX(unifrnd(xMin, xMax, prices.size()));
        p.setV(std::list<float>(prices.size()));
        p.setJ(funObj(p.getX(), prices, value));
        p.Best = new Particle(p); 
        if(p.Best->getJ() < Gbest.getJ()) {
        	Gbest.setX(p.getX());
        	Gbest.setJ(p.getJ());
        }
    }
}
void Optimization(std::list<Particle>& P, Particle& Gbest, std::list<float> prices, float value) {
	float kappa = 1;
	float phi1 = 2.05;
	float phi2 = 2.05;
	float phi = phi1 + phi2;
	float I = kappa / std::abs(2 - phi - std::sqrt(phi * phi - 4 * phi));
	float c1 = I*phi1;
	float c2 = I*phi2;
	while(Gbest.getJ() >= 0.864584) {
		for(auto& p : P) {
			std::list<float> xl = p.getX();
			std::list<float> vl = p.getV();
			std::list<float> bxl = p.Best->getX();
			std::list<float> gbxl = Gbest.getX();
			auto it_x = xl.begin();
			auto it_v = vl.begin();
			auto it_bx = bxl.begin();
			auto it_gbx = gbxl.begin();
			float x, v, bx, gbx; 
			while(it_x != xl.end()) {
				x = *it_x; 
				v = *it_v;
				bx = *it_bx;
				gbx = *it_gbx; 
				
				v = I * v + c1 * randa() * (bx - x) + c2 * randa() * (gbx - x);
				x = x + v;
				*it_x = x;
				*it_v = v;
				
				it_x++;
				it_v++;
				it_bx++;
				it_gbx++;
			}
			p.setX(xl);
			p.setV(vl);
			p.setJ(funObj(p.getX(), prices, value));
			if(p.getJ() < p.Best->getJ()) {
				p.Best->setX(p.getX()); 
				p.Best->setJ(p.getJ()); 
				if(p.Best->getJ() < Gbest.getJ()) {
					Gbest.setX(p.Best->getX());
					Gbest.setJ(p.Best->getJ());
				}
			}
		}
		std::cout << "GBest::J::-> " << Gbest.getJ() << std::endl;
	}
}

int main(int argc, char** argv) {
    std::list<Particle> P(N);
    Particle Gbest = Particle();
    Gbest.setJ(INF);
    
    float cremeLeite = 3.48*2.0/200.0;
    float leiteCond = 5.74/395.0;
    float leiteNinho = 17.9/380.0; 
    
    std::list<float> prices = {cremeLeite, leiteCond, leiteNinho};
    float value = 8.60; 
    InitP(P, Gbest, prices, value);
    Optimization(P, Gbest, prices, value);
    Gbest.toString();
    return 0;
}

