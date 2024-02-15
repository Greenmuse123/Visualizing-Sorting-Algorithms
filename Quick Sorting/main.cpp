#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <random>
#include <chrono>

// Function prototypes
void drawArray(sf::RenderWindow& window, const std::vector<int>& array);
int partition(sf::RenderWindow& window, std::vector<int>& array, int low, int high);
void quickSort(sf::RenderWindow& window, std::vector<int>& array, int low, int high);

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

        quickSort(window, array, 0, array.size() - 1);
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

int partition(sf::RenderWindow& window, std::vector<int>& array, int low, int high) {
    int pivot = array[high];  
    int i = (low - 1);  

    for (int j = low; j <= high - 1; j++) {
        if (array[j] < pivot) {
            i++;  
            std::swap(array[i], array[j]);
            drawArray(window, array);
        }
    }
    std::swap(array[i + 1], array[high]);
    drawArray(window, array);
    return (i + 1);
}

void quickSort(sf::RenderWindow& window, std::vector<int>& array, int low, int high) {
    if (low < high) {
        int pi = partition(window, array, low, high);

        quickSort(window, array, low, pi - 1);
        quickSort(window, array, pi + 1, high);
    }
}
