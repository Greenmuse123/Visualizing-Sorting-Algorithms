#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <random>
#include <chrono>

// Function prototypes
void drawArray(sf::RenderWindow& window, const std::vector<int>& array);
void heapify(sf::RenderWindow& window, std::vector<int>& array, int n, int i);
void heapSort(sf::RenderWindow& window, std::vector<int>& array);

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

        heapSort(window, array);
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

void heapify(sf::RenderWindow& window, std::vector<int>& array, int n, int i) {
    int largest = i; // Initialize largest as root
    int left = 2 * i + 1; // left = 2*i + 1
    int right = 2 * i + 2; // right = 2*i + 2

    // If left child is larger than root
    if (left < n && array[left] > array[largest])
        largest = left;

    // If right child is larger than largest so far
    if (right < n && array[right] > array[largest])
        largest = right;

    // If largest is not root
    if (largest != i) {
        std::swap(array[i], array[largest]);

        // Recursively heapify the affected sub-tree
        heapify(window, array, n, largest);
    }
}

void heapSort(sf::RenderWindow& window, std::vector<int>& array) {
    int n = array.size();

    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(window, array, n, i);

    // One by one extract an element from heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        std::swap(array[0], array[i]);

        // call max heapify on the reduced heap
        heapify(window, array, i, 0);

        drawArray(window, array); // Visualize the sorting step
        sf::sleep(sf::milliseconds(30)); // Adjust the delay as needed
    }
}
