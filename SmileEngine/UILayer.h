#pragma once

namespace dae
{
	class Subject;

	class UILayer
	{
	public:
		UILayer(const glm::vec2& pos, const std::string& name);
		virtual ~UILayer() noexcept = default;

		virtual void Render() = 0;
		const std::string& GetName() const;

	protected:
		glm::vec2 m_Position;

	private:
		std::string m_Name;
	};
}

