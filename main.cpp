#include <iostream>
#include <cmath>
#include <cstdio>

using namespace std;

int main() {

    double a, b, c, d, e, f;
    // axx + bxy + cyy + dx + ey + f = 0
    cin >> a >> b >> c >> d >> e >> f;

    // чтобы все выводилось в нужном формате
    // (без e и с определенным количеством знаков после точки)
    cout.precision(12);
    cout << fixed;

    if (b != 0) {
        // если b != 0, имел место поворот - повернем обратно
        double phi = atan2(b, a - c) / 2;
        double c_phi = cos(phi), s_phi = sin(phi);
        double
                a_new = a * c_phi * c_phi + b * c_phi * s_phi + c * s_phi * s_phi,
                b_new = 0,
                c_new = a * s_phi * s_phi - b * c_phi * s_phi + c * c_phi * c_phi,
                d_new = d * c_phi + e * s_phi,
                e_new = d * -s_phi + e * c_phi;
        a = a_new, b = b_new, c = c_new, d = d_new, e = e_new;
    }
    // теперь b = 0, кривая либо горизонтальная, либо вертикальная

    if (a == 0) {
        // если отсутствует коэффициент при xx, сделаем симметрию относительно x = y
        // это просто замена x на y и наоборот
        swap(a, c);
        swap(d, e);
    }
    if (a < 0) {
        // если старший коэффициент отрицательный, мы работаем с чем-то вида -xx + yy = 0
        // намного приятнее, когда вид каноничный, то есть xx - yy = 0
        // для этого умножим все коэффициенты на -1, это поворот на 180 градусов
        a = -a, c = -c, d = -d, e = -e, f = -f;
    }
    // теперь либо a != 0, либо (a == 0 и c == 0, то есть кривая не квадратичная)

    if (a == 0) {
        // если это неквадратичная кривая
        if (d == 0 && e == 0) {
            if (f == 0)
                // 0 = 0
                cout << "Identity" << endl;
            else
                // non-0 = 0
                cout << "Empty set" << endl;
        } else {
            // dx + ey + f = 0, d != 0 или e != 0
            cout << "Straight line" << endl;
        }
        return 0;
    }
    // теперь a != 0

    if (a != 0 && d != 0) { // проверка на a != 0 лишняя, только для симметрии
        // если есть слагаемые вида axx + dx, представим как a (x + d / (2a))^2 - dd / (4a)
        // это соответствует сдвигу по x на -d / (2a), сделаем замену x -> x + d/(2a)
        f = f - d * d / 4 / a;
        d = 0;
    }
    if (c != 0 && e != 0) {
        // аналогично со сдвигом по y
        f = f - e * e / 4 / c;
        e = 0;
    }
    // теперь осталось что-то одного из видов axx + cyy + f = 0, axx + ey + f = 0
    // при чем a > 0, про остальные коэффициенты ничего не известно

    if (c == 0) {
        // axx + ey + f = 0
        if (e == 0) {
            // axx = -f
            if (f < 0)
                // x = +-sqrt(-f / a), y - любой
                cout << "Two straight lines" << endl;
            else if (f == 0)
                // x = 0, y - любой
                cout << "Straight line" << endl;
            else
                // axx = -f < 0, нет решений
                cout << "Empty set" << endl;
        } else {
            // y = (-axx - f) / e
            cout << "Parabola, eccentricity = " << 1.0 << endl;
        }
        return 0;
    }
    // остался только случай axx + cyy + f = 0

    if (c > 0) {
        // axx + cyy = -f, a > 0, c > 0, это эллипс
        if (f < 0)
            // xx / (-f/a) + yy / (-f/c) = 1
            // ecc = sqrt(1 - min(a, c)/max(a, c))
            cout << "Ellipsis, eccentricity = " << sqrt(1 - min(a, c) / max(a, c)) << endl;
        else if (f == 0)
            // axx + cyy = 0, только (0, 0) подходит
            cout << "Point" << endl;
        else
            // axx + byy = -f < 0, нет решений
            cout << "Empty set" << endl;
    } else {
        // axx + cyy = -f, a > 0, c < 0, это гипербола
        if (f == 0)
            // axx = -cyy, x = +-sqrt(c / a) * y
            cout << "Two intersecting straight lines" << endl;
        else if (f < 0)
            // xx / (-f/a) - yy / (-f/-c) = 1
            // ecc = sqrt(1 + a/-c)
            cout << "Hyperbola, eccentricity = " << sqrt(1 + a / -c) << endl;
        else
            // yy / (f/-c) - xx / (f/a) = 1
            // ecc = sqrt(1 + -c/a)
            cout << "Hyperbola, eccentricity = " << sqrt(1 + -c / a) << endl;
    }
}