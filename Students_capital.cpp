#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Laptop {
    int gains;
    int price;
    int index;
};

class GainsComparator {
public:
    bool operator()(const Laptop& a, const Laptop& b) const { return a.gains < b.gains; }
};

int maximalCapital(int N, int C, vector<int> gains, vector<int> prices)
{
    int number = gains.size();
    vector<Laptop> laptops;

    for (int i = 0; i < number; i++) {
        laptops.push_back({ gains[i], prices[i], i });
    }

    sort(laptops.begin(), laptops.end(), [](const Laptop& a, const Laptop& b) {return a.price < b.price; });

    priority_queue<Laptop, vector<Laptop>, GainsComparator> priorityQueue;

    int index = 0;
    for (int i = 0; i < N; i++) {
        while (index < number && laptops[index].price <= C) {
            priorityQueue.push(laptops[index++]);
        }

        if (priorityQueue.empty()) {
            break;
        }

        C += priorityQueue.top().gains;
        priorityQueue.pop();
    }

    return C;
}

int main()
{
    int N, k;
    int C;

    cout << "Enter number of laptops you can buy: ";
    cin >> N;

    cout << "Enter your initial capital: ";
    cin >> C;

    cout << "Enter number of available laptops: ";
    cin >> k;

    vector<int> gains(k);
    vector<int> prices(k);

    cout << "Enter gains for each laptop: ";
    for (int i = 0; i < k; ++i) {
        cin >> gains[i];
    }

    cout << "Enter prices for each laptop: ";
    for (int i = 0; i < k; ++i) {
        cin >> prices[i];
    }

    int finalCapital = maximalCapital(N, C, gains, prices);
    cout << "Final capital after summer: " << finalCapital << endl;

    return 0;
}