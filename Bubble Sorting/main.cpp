#include <SFML/Graphics.hpp>
#include <SFML/System.hpp> // For sf::sleep
#include <vector>
#include <random>
#include <chrono>

// Function prototypes
void drawArray(sf::RenderWindow& window, const std::vector<int>& array);
void bubbleSort(sf::RenderWindow& window, std::vector<int>& array);

int main() {
     sf::RenderWindow window(sf::VideoMode(800, 600), "Sorting Visualization");

    // Random number generation setup
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> distribution(10, 590); // Adjust range as needed

    std::vector<int> array;
    for (int i = 0; i < 100; ++i) { // For example, 100 elements
        array.push_back(distribution(generator));
    }

bool sorted = false; // Flag to check if the array has been sorted

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (!sorted) {
            bubbleSort(window, array);
            sorted = true; // Prevent further sorting after the first completion
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

void bubbleSort(sf::RenderWindow& window, std::vector<int>& array) {
    bool swapped = true;
    while (swapped) {
        swapped = false;
        for (size_t i = 1; i < array.size(); ++i) {
            if (array[i - 1] > array[i]) {
                std::swap(array[i - 1], array[i]);
                drawArray(window, array);
                sf::sleep(sf::milliseconds(10)); // Slow down the visualization
                swapped = true;
            }
        }
    }
}
