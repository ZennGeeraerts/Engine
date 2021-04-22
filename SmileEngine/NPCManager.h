#pragma once
#include <utility>
#include <vector>
#include <iostream>

class NPC
{
	std::string m_name;
	int m_Health;
public:
	explicit NPC(std::string name) : m_name(std::move(name)), m_Health{ 100 } {}
	const std::string& get_name() const { return m_name; }
	int GetHealth() const { return m_Health; }
	void SetHealth(int health) { m_Health = health; }
};

class NPCManager
{
	std::vector<NPC> m_npcs;
public:
	static NPCManager& GetInstance()
	{
		static NPCManager instance{};
		return instance;
	}

	void AddNPC(const std::string& name)
	{
		m_npcs.emplace_back(NPC(name));
	}

	void RemoveNPC(const std::string& name)
	{
		m_npcs.erase(std::remove_if(m_npcs.begin(), m_npcs.end(),
			[name](NPC& npc) {return npc.get_name() == name; }), m_npcs.end());
	}

	void Dump()
	{
		std::cout << "Available NPC's:" << std::endl;
		for (const auto& npc : m_npcs)
			std::cout << "NPC " << npc.get_name() << " with health: " << npc.GetHealth() << std::endl;
		std::cout << "NPC count:" << m_npcs.size() << std::endl;
	}

	void SetHealth(const std::string& name, int health)
	{
		auto it = std::find_if(m_npcs.begin(), m_npcs.end(),
			[name](NPC& npc) {return npc.get_name() == name; });
		(*it).SetHealth(health);
	}
};
