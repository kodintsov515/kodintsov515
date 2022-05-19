#include "AOIntegrals.h"

AOIntegrals::AOIntegrals(const Molecule& mol)
{
    map<Atom,BSonAtom> molecule_with_BS; 
    map<Atom,BSonAtom>::iterator Atoms=molecule_with_BS.begin();
    map<int, std::vector<std::vector<radial_t>>>::iterator Shells = Atoms->second.begin();
    size_t nBF = Shells->second.size();
    Matrix S(nBF,nBF) ;
    Sij OverlapMatrix;
    OverlapMatrix.calculate(S,nBF);
    
}

AOIntegrals::AOIntegrals(const std::string& filename) {}

void AOIntegrals::saveToFile(const std::string& filename) const {}

void Eijt::calculate(const Atom* A, const Atom* B, char direction, int shell, int subshell, int orbital, size_t i_max, size_t j_max)
{
    map<Atom,BSonAtom>::iterator atomA = molecule_with_BS.find(*A); // ищем в молекуле атом A
    map<Atom,BSonAtom>::iterator atomB = molecule_with_BS.find(*B);
    map<int, std::vector<std::vector<radial_t>>>::iterator shellA = atomA->second.find(shell); // ищем оболочку атома A с номером shell
    map<int, std::vector<std::vector<radial_t>>>::iterator shellB = atomB->second.find(shell);
    double* a = &(shellA->second[shell][subshell][orbital].a); // извлекаем параметры
    double* b = &(shellB->second[shell][subshell][orbital].a);  
    this->E.e[0][0][0]=this->calculate_zero_element(&(atomA->first), &(atomB->first), a, b, direction); // вычисляем нулевой элемент E000
    Atom* P=A->calculate_P(B,a,b) ; // вычисляем фиктивный(q=0) P атом между атомами A и B
    for(size_t j=0;j<=j_max;j++) // заполняем весь тензор Eijt для данных атомов, данной оболочки, данной оси и данных i_max,j_max; идем послойно, слои нумеруются индексом j
    {
        for(size_t i=0;i<=i_max;i++) // внутри слоя j шагем по индексу i
        {
            for(size_t t=0;t<=i;t++) // при фиксированных i и j шагаем по t
            {
                index upper;                          // эти индексы нужны при вычислении следующего элемента
                upper.i = i-1; upper.j=j; upper.t=t+1;
                index middle;
                middle.i=i-1; middle.j=j; middle.t=t;
                index lower;
                lower.i=i-1; lower.j=j;lower.t=t-1;  // то, что индекс может быть отрицательный не страшно, т.к. в функции-члене calculate_next_element значение все равно занулиться
                E.e[i][j][t] = this->calculate_next_element(P,A,a,b,&E.e[i-1][j][t-1],lower,&E.e[i-1][j][t+1],upper,&E.e[i-1][j][t],middle, direction); //  при фиксированном индексах i и j
            }                                                                                                                                    // вычисляем ненулевые Eijt (шаг по t)
        }
        for(size_t t=1;t<=j;t++) // при вычислении Eijt нужно заполнить также часть элементов E0jt (t>=1)
        {
            index upper;
            upper.i=0; upper.j=j-1; upper.t=t+1;
            index middle;
            middle.i=0; middle.j=j-1; middle.t=t;
            index lower;
            lower.i=0; lower.j=j-1; lower.t=t-1;
            E.e[0][j][t] = this->calculate_next_element(P, B, a, b, &E.e[0][j-1][t-1], lower, &E.e[0][j-1][t+1], upper, &E.e[0][j-1][t], middle, direction); 
        } 
    }
};

double Eijt::calculate_next_element(const Atom* P, const Atom* A, double* a, double* b, double* lower, index low_i, double* upper, index up_i,
double* middle, index mid_i, char direction)
{
    double p = *a + *b;
    double next;
    if(low_i.t<0)  *lower = 0;
    if(up_i.i==up_i.j==0) *upper=0;
    if(up_i.t>up_i.i) *upper = 0;
    if(mid_i.t>mid_i.i) *middle=0;
    switch(direction)
    {
        case 'x':
            {
                double Xpa = P->x_-A->x_;
                next = 1/(2*p)*(*lower)+(mid_i.t+1)*(*upper)+Xpa*(*middle);
            }
        case 'y':
            {
                double Ypa = P->y_-A->y_;
                next = 1/(2*p)*(*lower)+(mid_i.t+1)*(*upper)+Ypa*(*middle);
            }
        case 'z':
            {
                double Zpa = P->z_-A->z_;
                next = 1/(2*p)*(*lower)+(mid_i.t+1)*(*upper)+Zpa*(*middle);
            }
    }
    return next;
};

double Eijt::calculate_zero_element(const Atom* A,const Atom* B, double* a, double* b, char direction)
{
    double mu = (*a)*(*b)/(*a + *b);
    double zero_element;
    switch(direction) 
    {
        case 'x':
            {
                double Xab = A->x_ - B->x_;
                zero_element = exp(-mu*Xab*Xab);
            }
        case 'y':
            {
                double Yab = A->y_ - B->y_;
                zero_element = exp(-mu*Yab*Yab);
            }
        case 'z':
            {
                double Zab = A->z_ - B->z_;
                zero_element = exp(-mu*Zab*Zab);
            }
    }
    return zero_element;
};

void Sij::calculate(Matrix S, size_t nBF)
{
    /*Eijt Ex;
    Eijt Ey;
    Eijt Ez;
    Matrix Sij;
    pair<size_t, size_t> ij(0,0);
    pair<size_t, size_t> kl(0,0);
    for(; ij.first<nBF;ij.first++)
    {
        Atom* A = &atoms[ij.first];
        for(; ij.second<ij.first;ij.second++)
        {
            Atom* B = &atoms[ij.second];
            for(kl=ij;;)
            Ex.calculate();
            Ey.calculate();
            Ez.calculate();
            Sij[ij]; 
        }
    }*/
};