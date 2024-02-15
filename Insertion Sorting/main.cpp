#include <SFML/Graphics.hpp>
#include <SFML/System.hpp> // For sf::sleep
#include <vector>
#include <random>
#include <chrono>

// Function prototypes
void drawArray(sf::RenderWindow& window, const std::vector<int>& array);
void insertionSort(sf::RenderWindow& window, std::vector<int>& array);

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Sorting Visualization");

    // Random number generation setup
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> distribution(10, 590);

    std::vector<int> array;
    for (int i = 0; i < 100; ++i) {
        array.push_back(distribution(generator));
    }

    bool sorted = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (!sorted) {
            insertionSort(window, array);
            sorted = true;
        }
    }

    return 0;
}

void drawArray(sf::RenderWindow& window, const std::vector<int>& array) {
    window.clear();
    float barWidth = window.getSize().x / static_cast<float>(array.size());
    for (size_t i = 0; i < array.size(); ++i) {
        sf::RectangleShape bar(sf::Vector2f(barWidth - 1, array[i]));
        bar.setPosition(i * barWidth, window.getSize().y - array[i]);
        window.draw(bar);
    }
    window.display();
}

void insertionSort(sf::RenderWindow& window, std::vector<int>& array) {
    for (size_t i = 1; i < array.size(); i++) {
        int key = array[i];
        int j = i - 1;

        // Move elements of array[0..i-1], that are greater than key,
        // to one position ahead of their current position
        while (j >= 0 && array[j] > key) {
            array[j + 1] = array[j];
            j = j - 1;
            drawArray(window, array); // Visualize the sorting step
            sf::sleep(sf::milliseconds(75)); // Adjust the delay as needed
        }
        array[j + 1] = key;
    }
}
