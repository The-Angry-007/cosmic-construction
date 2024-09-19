#pragma once
void AddClicked();
void SelectClicked();
void DeleteClicked();
class Label;
class InputField;
class Slider;
class Panel;
class Gui
{
public:
	Label* fpsLabel;

	void Render(float dt);
	void Update();

	//whenever the mouse is over a button, it shouldnt select a planet behind the button or otherwise.
	bool mouseBlockedByGui;
	//to prevent weird sfml glitch where textures cause errors before renderwindow handle generated.
	void Init();

	void AddButton(Button button);
	void AddLabel(Label label);
	void AddPanel(Panel panel);
	void AddInpField(InputField field);
	void AddSlider(Slider slider);
	void RenderFps(float dt);
	Gui();
	//public so that contents can be read
	std::vector<InputField> inpFields;
	~Gui();

private:
	std::vector<Button> buttons;
	std::vector<Label> labels;
	std::vector<Panel> panels;
	std::vector<Slider> sliders;
};