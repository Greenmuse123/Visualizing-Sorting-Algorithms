#include <SFML/Graphics.hpp>
#include <SFML/System.hpp> // For sf::sleep
#include <vector>
#include <random>
#include <chrono>

// Function prototypes
void drawArray(sf::RenderWindow& window, const std::vector<int>& array);
void merge(sf::RenderWindow& window, std::vector<int>& array, int const left, int const mid, int const right);
void mergeSort(sf::RenderWindow& window, std::vector<int>& array, int const begin, int const end);

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

        mergeSort(window, array, 0, array.size() - 1);
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

void merge(sf::RenderWindow& window, std::vector<int>& array, int const left, int const mid, int const right) {
    auto const subArrayOne = mid - left + 1;
    auto const subArrayTwo = right - mid;

    // Create temp arrays
    std::vector<int> leftArray(subArrayOne), rightArray(subArrayTwo);

    // Copy data to temp arrays leftArray[] and rightArray[]
    for (auto i = 0; i < subArrayOne; i++)
        leftArray[i] = array[left + i];
    for (auto j = 0; j < subArrayTwo; j++)
        rightArray[j] = array[mid + 1 + j];

    auto indexOfSubArrayOne = 0, indexOfSubArrayTwo = 0;
    int indexOfMergedArray = left; // Initial index of merged array

    // Merge the temp arrays back into array[left..right]
    while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
        if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) {
            array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        } else {
            array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
        drawArray(window, array);
        sf::sleep(sf::milliseconds(30)); // Adjust as needed
    }

    // Copy the remaining elements of leftArray[], if there are any
    while (indexOfSubArrayOne < subArrayOne) {
        array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
        drawArray(window, array);
        sf::sleep(sf::milliseconds(30)); // Adjust as needed
    }

    // Copy the remaining elements of rightArray[], if there are any
    while (indexOfSubArrayTwo < subArrayTwo) {
        array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
        drawArray(window, array);
        sf::sleep(sf::milliseconds(30)); // Adjust as needed
    }
}

void mergeSort(sf::RenderWindow& window, std::vector<int>& array, int const begin, int const end) {
    if (begin >= end)
        return; // Returns recursively

    auto mid = begin + (end - begin) / 2;
    mergeSort(window, array, begin, mid);
    mergeSort(window, array, mid + 1, end);
    merge(window, array, begin, mid, end);
}
