/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Node.h"
#include "engine/Command.h"

namespace ai{

    Node::Node() {

    }

    Node::Node(int prof, int value, int player, std::vector<engine::Command*> commands) : prof(prof), value(value), player(player), commands(commands) {

    }

    int Node::getProf() const {
        return prof;
    }

    void Node::setProf(int prof) {
        prof = prof;
    }

    int Node::getValue() const {
        return value;
    }

    void Node::setValue(int value) {
        this->value = value;
    }

    void Node::addSon(Node* node) {
        sons.push_back(node);
    }

    Node* Node::getSon(int id) const {
        return sons[id];
    }

    const std::vector<engine::Command*>& Node::getCommands() const {
        return commands;
    }

    void Node::addCommand(engine::Command* command) {
        commands.push_back(command);
    }


    int Node::getSize() const {
        return sons.size();
    }

    int Node::getPlayer() const {
        return player;
    }

    void Node::setPlayer(int player) {
        player = player;
    }
    
    
    
}