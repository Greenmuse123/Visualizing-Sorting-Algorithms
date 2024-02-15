#include <SFML/Graphics.hpp>
#include <SFML/System.hpp> // For sf::sleep
#include <vector>
#include <random>
#include <chrono>

// Function prototypes
void drawArray(sf::RenderWindow& window, const std::vector<int>& array);
void selectionSort(sf::RenderWindow& window, std::vector<int>& array);

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Sorting Visualization");

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> distribution(10, 590);

    std::vector<int> array;
    for (int i = 0; i < 100; ++i) {
        array.push_back(distribution(generator));
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        selectionSort(window, array);
        drawArray(window, array); // Draw one last time to ensure the final state is visualized
        sf::sleep(sf::milliseconds(2000)); // Wait a bit before closing automatically or by user action
        break; // Exit the loop after sorting is done
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
    sf::sleep(sf::milliseconds(30)); // Slow down the visualization
}

void selectionSort(sf::RenderWindow& window, std::vector<int>& array) {
    size_t n = array.size();
    for (size_t i = 0; i < n-1; i++) {
        // Find the minimum element in unsorted array
        size_t min_idx = i;
        for (size_t j = i+1; j < n; j++)
            if (array[j] < array[min_idx])
                min_idx = j;

        // Swap the found minimum element with the first element
        std::swap(array[min_idx], array[i]);
        drawArray(window, array); // Visualize the sorting step
        sf::sleep(sf::milliseconds(30)); // Adjust the delay as needed
    }
}
