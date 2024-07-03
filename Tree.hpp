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


/**
 * @brief A class representing a tree data structure. 
**/
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
        
        /**
         * @brief Add a root node to the tree, if there is a root already it will be overwritten.
         * @param node The node to be set as the root of the tree.
         * @throw invalid_argument If the node is null. 
        **/
        int add_root(Node<T>* node);

        /**
         * @brief Add a child node to a parent node.
         * @param parent The parent node to which the child will be added.
         * @param child The child node to be added.
         * @throw invalid_argument If the parent is null.
         * @throw invalid_argument If the parent already has the maximum number of children. 
        **/
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

    /**
     * @brief Open a windwo and draw the tree.
    **/
    void drawTree()
    {
        sf::RenderWindow window(sf::VideoMode(1400, 1000), "Tree Visualization"); 
        while (window.isOpen()) 
        {
            // Keep displaying the window until it's closed
            sf::Event event; 
            while (window.pollEvent(event)) 
            {
                if (event.type == sf::Event::Closed) 
                    window.close();
            }

            window.clear(sf::Color::Black); 

            // Draw tree widgets
            drawTree(window, root, 650, 100, 200, 150); 

            // display new window
            window.display(); 
        }
    }

private:
   
    
    std::string formatData(const T &data, int precision = 5)
    {
        std::stringstream ss; 
        ss << std::fixed << std::setprecision(precision) << data; 
        return ss.str(); 
    }

    // Helper function to truncate text and add ellipsis if necessary
    std::string truncateText(const sf::Text &text, float maxWidth)
    {
        std::string str = text.getString(); 
        std::string truncatedStr = str; 
        sf::Text tempText = text; 

        
        if (text.getLocalBounds().width > maxWidth)
        {
            
            for (size_t i = 0; i < str.size(); ++i)
            {
                truncatedStr = str.substr(0, i) + "..."; 
                tempText.setString(truncatedStr); 

                if (tempText.getLocalBounds().width > maxWidth) 
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

        
        float totalWidth = 0.0f;
        for (auto &child : node->children)
        {
            totalWidth += calculateSubtreeWidth(child, xOffset) + xOffset;
        }

        totalWidth -= (2 * xOffset)  ;

        return std::max(totalWidth, xOffset);
    }

void drawTree(sf::RenderWindow &window, Node<T> *node, float x, float y, float xOffset, float yOffset)
{
    if (!node)
        return;

    // Draw the node
    sf::CircleShape circle(40);
    circle.setFillColor(sf::Color::Red);
    circle.setPosition(x, y);

    // Load the font
    sf::Font font;
    if (!font.loadFromFile("RobotoFlex-Regular.ttf"))
    {
        std::cerr << "Failed to load font\n";
        return;
    }

    // Format the node data for display with a precision of 5
    // std::string nodeDataStr = std::to_string(node->value);
    std::string nodeDataStr = formatData(node->value);

    // Create the text for the node data
    sf::Text text;
    text.setFont(font);
    text.setString(nodeDataStr);
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::Black);

    // Initial centering of text based on its original content
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

    float circleCenterX = x + circle.getRadius();
    float circleCenterY = y + circle.getRadius();

    text.setPosition(circleCenterX, circleCenterY);

    float maxTextWidth = circle.getRadius() * 2.0f - 10.0f; // Circle diameter minus padding
    std::string truncatedTextStr = truncateText(text, maxTextWidth);
    text.setString(truncatedTextStr);

    textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

    text.setPosition(circleCenterX, circleCenterY);

    window.draw(circle);
    window.draw(text);

    int numChildren = 0;
    for(size_t i = 0; i < node->children.size(); i++)
    {
        if(node->children[i] != nullptr)
        {
            numChildren++;
        }
    }
    if (numChildren > 0)
    {
        float subtreeWidth = calculateSubtreeWidth(node, xOffset);

        float startX = x + circle.getRadius() - subtreeWidth / 2.0f;

        for (size_t i = 0; i <= numChildren; ++i)
        {
            if(node->children[i] == nullptr)
            {
                continue;
            }
            float childX = startX + i * (subtreeWidth );
            float childY = y + yOffset;

            // Draw the connecting line
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(circleCenterX, circleCenterY), sf::Color::White),
                sf::Vertex(sf::Vector2f(childX + circle.getRadius(), childY + circle.getRadius()), sf::Color::Black)};
            window.draw(line, 2, sf::Lines);

            // Recursively draw the child node
            drawTree(window, node->children[i], childX, childY, xOffset / 1.2f, yOffset);
        }
    }

    // Check if the user hovers on the node and display
    // tooltip box with the whole number value
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    if (circle.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
    {
        sf::RectangleShape tooltip(sf::Vector2f(200, 50));
        tooltip.setFillColor(sf::Color(255, 255, 255, 200)); 
        tooltip.setOutlineColor(sf::Color::Black);
        tooltip.setOutlineThickness(1);
        tooltip.setPosition(static_cast<float>(mousePos.x) + 10, static_cast<float>(mousePos.y) - 60);

        
        sf::Text tooltipText;
        tooltipText.setFont(font);
        tooltipText.setString(nodeDataStr); 
        tooltipText.setCharacterSize(20);
        tooltipText.setFillColor(sf::Color::Black);
        tooltipText.setPosition(tooltip.getPosition().x + 10, tooltip.getPosition().y + 10);

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

/**
 * @brief Specialization of the Tree class for binary trees.
**/
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
        
        /**
         * @brief Add a root node to the tree, if there is a root already it will be overwritten.
         * @param node The node to be set as the root of the tree.
         * @throw invalid_argument If the node is null.
        **/
        int add_root(Node<T>* node);

        /**
         * @brief Add a child node to a parent node.
         * @param parent The parent node to which the child will be added.
         * @param child The child node to be added.
         * @throw invalid_argument If the parent is null.
         * @throw invalid_argument If the parent already has the maximum number of children. 
        **/
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

    /**
     * @brief Open a windwo and draw the tree.
    **/
    void drawTree()
    {
        sf::RenderWindow window(sf::VideoMode(1400, 1000), "Tree Visualization"); 
        while (window.isOpen()) 
        {
            // Keep displaying the window until it's closed
            sf::Event event; 
            while (window.pollEvent(event)) 
            {
                if (event.type == sf::Event::Closed) 
                    window.close();
            }

            window.clear(sf::Color::Black); 

            // Draw tree widgets
            drawTree(window, root, 650, 100, 200, 150); 

            // display new window
            window.display(); 
        }
    }

    private:
   
        std::string formatData(const T &data, int precision = 5)
        {
            std::stringstream ss; 
            ss << std::fixed << std::setprecision(precision) << data; 
            return ss.str(); 
        }

        // Helper function to truncate text and add ellipsis if necessary
        std::string truncateText(const sf::Text &text, float maxWidth)
        {
            std::string str = text.getString(); 
            std::string truncatedStr = str; 
            sf::Text tempText = text; 

            
            if (text.getLocalBounds().width > maxWidth)
            {
                for (size_t i = 0; i < str.size(); ++i)
                {
                    truncatedStr = str.substr(0, i) + "..."; 
                    tempText.setString(truncatedStr); 

                    if (tempText.getLocalBounds().width > maxWidth) 
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

            
            float totalWidth = 0.0f;
            for (auto &child : node->children)
            {
                totalWidth += calculateSubtreeWidth(child, xOffset) + xOffset;
            }

            totalWidth -= (2 * xOffset)  ;

            return std::max(totalWidth, xOffset);
        }

        void drawTree(sf::RenderWindow &window, Node<T> *node, float x, float y, float xOffset, float yOffset)
        {
        if (!node)
            return;

        // Draw the node
        sf::CircleShape circle(40);
        circle.setFillColor(sf::Color::Red);
        circle.setPosition(x, y);

        // Load the font
        sf::Font font;
        if (!font.loadFromFile("RobotoFlex-Regular.ttf"))
        {
            std::cerr << "Failed to load font\n";
            return;
        }

        // Format the node data for display with a precision of 5
        // std::string nodeDataStr = std::to_string(node->value);
        std::string nodeDataStr = formatData(node->value);

        // Create the text for the node data
        sf::Text text;
        text.setFont(font);
        text.setString(nodeDataStr);
        text.setCharacterSize(30);
        text.setFillColor(sf::Color::Black);

        // Initial centering of text based on its original content
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

        float circleCenterX = x + circle.getRadius();
        float circleCenterY = y + circle.getRadius();

        text.setPosition(circleCenterX, circleCenterY);

        float maxTextWidth = circle.getRadius() * 2.0f - 10.0f; // Circle diameter minus padding
        std::string truncatedTextStr = truncateText(text, maxTextWidth);
        text.setString(truncatedTextStr);

        textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

        text.setPosition(circleCenterX, circleCenterY);

        window.draw(circle);
        window.draw(text);

        int numChildren = 0;
        for(size_t i = 0; i < node->children.size(); i++)
        {
            if(node->children[i] != nullptr)
            {
                numChildren++;
            }
        }
        if (numChildren > 0)
        {
            float subtreeWidth = calculateSubtreeWidth(node, xOffset);

            float startX = x + circle.getRadius() - subtreeWidth / 2.0f;

            for (size_t i = 0; i <= numChildren; ++i)
            {
                if(node->children[i] == nullptr)
                {
                    continue;
                }
                float childX = startX + i * (subtreeWidth );
                float childY = y + yOffset;

                // Draw the connecting line
                sf::Vertex line[] = {
                    sf::Vertex(sf::Vector2f(circleCenterX, circleCenterY), sf::Color::White),
                    sf::Vertex(sf::Vector2f(childX + circle.getRadius(), childY + circle.getRadius()), sf::Color::Black)};
                window.draw(line, 2, sf::Lines);

                // Recursively draw the child node
                drawTree(window, node->children[i], childX, childY, xOffset / 1.2f, yOffset);
            }
        }

        // Check if the user hovers on the node and display
        // tooltip box with the whole number value
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (circle.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
        {
            sf::RectangleShape tooltip(sf::Vector2f(200, 50));
            tooltip.setFillColor(sf::Color(255, 255, 255, 200)); 
            tooltip.setOutlineColor(sf::Color::Black);
            tooltip.setOutlineThickness(1);
            tooltip.setPosition(static_cast<float>(mousePos.x) + 10, static_cast<float>(mousePos.y) - 60);

            
            sf::Text tooltipText;
            tooltipText.setFont(font);
            tooltipText.setString(nodeDataStr); 
            tooltipText.setCharacterSize(20);
            tooltipText.setFillColor(sf::Color::Black);
            tooltipText.setPosition(tooltip.getPosition().x + 10, tooltip.getPosition().y + 10);

            window.draw(tooltip);
            window.draw(tooltipText);
        }
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
