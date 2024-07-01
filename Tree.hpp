// @author: oz.atar@msmail.ariel.ac.il

#pragma once

#include <SFML/Graphics.hpp>

#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <stdexcept>
#include <iostream>
using std::vector;
using std::stack;
using std::queue;
using std::invalid_argument;
using std::cout;
using std::endl;

#include "Iterators.hpp"
#include "Node.hpp"
#include "Complex.hpp"
#include <sstream>
#include <cmath>
#include <iomanip>  

template <typename T, size_t max_children = 2>
class Tree
{
    private:
        Node<T>* root;
    public:

        /** 
         * @brief Default constructor, create a binary tree.
        **/
        Tree() : root(nullptr) {};
        
        int add_root(Node<T>* node);

        int add_sub_node(Node<T> *parent, Node<T>* child);

        int get_max_children() const
        {
            return max_children;
        }
        Dfs_scan<T> pre_order_begin()
        {
            return Dfs_scan<T>(this->root);
        }

        Dfs_scan<T> pre_order_end()
        {
            return Dfs_scan<T>(nullptr);
        }

        Dfs_scan<T> post_order_begin()
        {
            return Dfs_scan<T>(this->root);
        }

        Dfs_scan<T> post_order_end()
        {
            return Dfs_scan<T>(nullptr);
        }

        Dfs_scan<T> in_order_begin()
        {
            return Dfs_scan<T>(this->root);
        }

        Dfs_scan<T> in_order_end()
        {
            return Dfs_scan<T>(nullptr);
        }

        Dfs_scan<T> begin_dfs_scan()
        {
            return Dfs_scan<T>(this->root);
        }

        Dfs_scan<T> end_dfs_scan()
        {
            return Dfs_scan<T>(nullptr);
        }

        Bfs_scan<T> begin_bfs_scan()
        {
            return Bfs_scan<T>(this->root);
        }

        Bfs_scan<T> end_bfs_scan()
        {
            return Bfs_scan<T>(nullptr);
        }

        Bfs_scan<T> begin()
        {
            return Bfs_scan<T>(this->root);
        }

        Bfs_scan<T> end()
        {
            return Bfs_scan<T>(nullptr);
        }

        heapIterator<T> heap_begin()
        {
            return heapIterator<T>(this->root);
        }
        heapIterator<T> heap_end()
        {
            return heapIterator<T>(nullptr);
        }

    void draw()
    {
        sf::RenderWindow window(sf::VideoMode(800, 600), "Tree Visualization"); // Create a window
        while (window.isOpen()) // While the window is open
        {
            sf::Event event; // Create an event
            while (window.pollEvent(event)) // While there are events to process
            {
                if (event.type == sf::Event::Closed) // If the event is a close event, close the window
                    window.close();
            }

            window.clear(sf::Color::White); // Clear the window, set the background color to white

            drawTree(window, root, 400, 50, 150, 100, 0); //calls the drawTree function to draw the tree

            window.display(); // Display the window
        }
    }

private:
   
    // Helper function to format numbers with a specific precision
    std::string formatData(const T &data, int precision = 5)
    {
        std::stringstream ss; // Create a stringstream
        ss << std::fixed << std::setprecision(precision) << data; // Set the precision of the stringstream
        return ss.str(); // Return the string
    }

    // Helper function to truncate text and add ellipsis if necessary
    std::string truncateText(const sf::Text &text, float maxWidth)
    {
        std::string str = text.getString(); // Get the string from the text
        std::string truncatedStr = str; // Set the truncated string to the original string
        sf::Text tempText = text; // Create a temporary text object

        // Check if the text width exceeds the maximum allowed width
        if (text.getLocalBounds().width > maxWidth)
        {
            // Find the maximum length that fits within the width
            for (size_t i = 0; i < str.size(); ++i)
            {
                truncatedStr = str.substr(0, i) + "..."; // Add ellipsis to the string
                tempText.setString(truncatedStr); // Set the string of the temporary text object

                if (tempText.getLocalBounds().width > maxWidth) //if the text is too long, truncate it
                {
                    truncatedStr = str.substr(0, i - 1) + "...";
                    break;
                }
            }
        }
        return truncatedStr;
    }

    float calculateSubtreeWidth(Node<T> *node, float xOffset)
    {
        if (!node || node->children.empty())
            return 0.0f;

        // Sum the widths of all children subtrees
        float totalWidth = 0.0f;
        for (auto &child : node->children)
        {
            totalWidth += calculateSubtreeWidth(child, xOffset) + xOffset;
        }

        // The total width should be adjusted by removing the extra xOffset added to the last child
        totalWidth -= (2 * xOffset)  ;

        // Ensure at least a minimum width for a single child
        return std::max(totalWidth, xOffset);
    }

void drawTree(sf::RenderWindow &window, Node<T> *node, float x, float y, float xOffset, float yOffset, int level)
{
    if (!node)
        return;

    // Draw the node
    sf::CircleShape circle(30);
    circle.setFillColor(sf::Color::Green);
    circle.setPosition(x, y);

    // Load the font
    sf::Font font;
    if (!font.loadFromFile("RobotoFlex-Regular.ttf"))
    {
        std::cerr << "Failed to load font\n";
        return;
    }

    // Format the node data for display with a precision of 5
    std::string nodeDataStr = formatData(node->value);

    // Create the text for the node data
    sf::Text text;
    text.setFont(font);
    text.setString(nodeDataStr);
    text.setCharacterSize(15);
    text.setFillColor(sf::Color::Black);

    // Initial centering of text based on its original content
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

    // Calculate the circle's center
    float circleCenterX = x + circle.getRadius();
    float circleCenterY = y + circle.getRadius();

    // Set the initial position of the text to the circle's center
    text.setPosition(circleCenterX, circleCenterY);

    // Truncate the text if it doesn't fit within the circle
    float maxTextWidth = circle.getRadius() * 2.0f - 10.0f; // Circle diameter minus padding
    std::string truncatedTextStr = truncateText(text, maxTextWidth);
    text.setString(truncatedTextStr);

    // Re-calculate the origin after setting the truncated text to ensure it's centered
    textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

    // Adjust the position again to ensure the truncated text is centered within the circle
    text.setPosition(circleCenterX, circleCenterY);

    // Draw the circle and text
    window.draw(circle);
    window.draw(text);

    // Calculate the positions for the children
    int numChildren = node->children.size();
    if (numChildren > 0)
    {
        // Calculate the width needed for the current node's subtree
        float subtreeWidth = calculateSubtreeWidth(node, xOffset);

        // Calculate the start position for the first child node
        float startX = x + circle.getRadius() - subtreeWidth / 2.0f;

        for (size_t i = 0; i < numChildren; ++i)
        {
            float childX = startX + i * (subtreeWidth / numChildren);
            float childY = y + yOffset;

            // Draw the connecting line
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(circleCenterX, circleCenterY), sf::Color::Black),
                sf::Vertex(sf::Vector2f(childX + circle.getRadius(), childY + circle.getRadius()), sf::Color::Black)};
            window.draw(line, 2, sf::Lines);

            // Recursively draw the child node
            drawTree(window, node->children[i], childX, childY, xOffset / 1.2f, yOffset, level + 1);
        }
    }

    // Check if the mouse is hovering over the circle
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    if (circle.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
    {
        // Create and position the tooltip box
        sf::RectangleShape tooltip(sf::Vector2f(200, 50));
        tooltip.setFillColor(sf::Color(255, 255, 255, 200)); // Semi-transparent white
        tooltip.setOutlineColor(sf::Color::Black);
        tooltip.setOutlineThickness(1);
        tooltip.setPosition(static_cast<float>(mousePos.x) + 10, static_cast<float>(mousePos.y) - 60);

        // Create and position the tooltip text
        sf::Text tooltipText;
        tooltipText.setFont(font);
        tooltipText.setString(nodeDataStr); // Full untruncated text
        tooltipText.setCharacterSize(15);
        tooltipText.setFillColor(sf::Color::Black);
        tooltipText.setPosition(tooltip.getPosition().x + 10, tooltip.getPosition().y + 10);

        // Draw the tooltip box and text
        window.draw(tooltip);
        window.draw(tooltipText);
    }
}
};

template <typename T, size_t max_children>
int Tree<T, max_children>::add_root(Node<T>* node)
{
    if (node == nullptr) 
    {
        throw std::invalid_argument("Can not initialize tree with a null node.");
    }
    this->root = node;
    return 0;
}

template <typename T, size_t max_children>
int Tree<T, max_children>::add_sub_node(Node<T> *parent, Node<T>* child) {
    if (parent == nullptr) {
        throw std::invalid_argument("Can not add a child to a null parent.");
    }
    if(parent->children.size() == max_children) {
        throw std::invalid_argument("Parent node already has the maximum number of children.");
    }
    parent->children.push_back(child);
    return 0;
}

template <typename T>
class Tree<T, 2>
{
    private:
        Node<T>* root;
    public:

        /** 
         * @brief Default constructor, create a binary tree.
        **/
        Tree() : root(nullptr) {};
        
        int add_root(Node<T>* node);

        int add_sub_node(Node<T> *parent, Node<T>* child);

        int get_max_children() const
        {
            return 2;
        }

    PreOrderIterator<T> pre_order_begin()
    {
        return PreOrderIterator<T>(this->root);
    }

    PreOrderIterator<T> pre_order_end()
    {
        return PreOrderIterator<T>(nullptr);
    }

    PostOrderIterator<T> post_order_begin()
    {
        return PostOrderIterator<T>(this->root);
    }

    PostOrderIterator<T> post_order_end()
    {
        return PostOrderIterator<T>(nullptr);
    }

    InOrderIterator<T> in_order_begin()
    {
        return InOrderIterator<T>(this->root);
    }

    InOrderIterator<T> in_order_end()
    {
        return InOrderIterator<T>(nullptr);
    }

    Dfs_scan<T> begin_dfs_scan()
    {
        return Dfs_scan<T>(this->root);
    }

    Dfs_scan<T> end_dfs_scan()
    {
        return Dfs_scan<T>(nullptr);
    }

    Bfs_scan<T> begin_bfs_scan()
    {
        return Bfs_scan<T>(this->root);
    }

    Bfs_scan<T> end_bfs_scan()
    {
        return Bfs_scan<T>(nullptr);
    }

    static Bfs_scan<T> begin_bfs_scan(Node<T>* root)
    {
        return Bfs_scan<T>(root);
    }

    static Bfs_scan<T> end_bfs_scan(Node<T>* root)
    {
        return Bfs_scan<T>(nullptr);
    }

    Bfs_scan<T> begin()
    {
        return Bfs_scan<T>(this->root);
    }

    Bfs_scan<T> end()
    {
        return Bfs_scan<T>(nullptr);
    }

    heapIterator<T> heap_begin()
    {
        return heapIterator<T>(this->root);
    }
    heapIterator<T> heap_end()
    {
        return heapIterator<T>(nullptr);
    }
};

template <typename T>
int Tree<T, 2>::add_root(Node<T>* node)
{
    if (node == nullptr) 
    {
        throw std::invalid_argument("Can not initialize tree with a null node.");
    }
    this->root = node;
    return 0;
}

template <typename T>
int Tree<T, 2>::add_sub_node(Node<T> *parent, Node<T>* child) 
{
    if (parent == nullptr) {
        throw std::invalid_argument("Can not add a child to a null parent.");
    }
    if(parent->children.size() == 2) {
        throw std::invalid_argument("Parent node already has the maximum number of children.");
    }
    parent->children.push_back(child);
    return 0;
}
