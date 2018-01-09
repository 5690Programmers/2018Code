#include <iostream>
#include <memory>
#include <string>

#include <Joystick.h>
#include <SampleRobot.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include <Drive/DifferentialDrive.h>
#include <Timer.h>
#include <PWMTalonSRX.h>
#include <SpeedControllerGroup.h>
/**
 * This is a demo program showing the use of the RobotDrive class.
 * The SampleRobot class is the base of a robot application that will
 * automatically call your Autonomous and OperatorControl methods at the right
 * time as controlled by the switches on the driver station or the field
 * controls.
 *
 * WARNING: While it may look like a good choice to use for your code if you're
 * inexperienced, don't. Unless you know what you are doing, complex code will
 * be much more difficult under this system. Use IterativeRobot or Command-Based
 * instead if you're new.
 */
class Robot: public frc::SampleRobot {

	frc::PWMTalonSRX Arm{4};


	frc::PWMTalonSRX front_left {0};
	frc::PWMTalonSRX back_left {1};
	frc::PWMTalonSRX front_right {3};
	frc::PWMTalonSRX back_right {2};

	frc::SpeedControllerGroup left{front_left, back_left};
	frc::SpeedControllerGroup right{front_right, back_right};

	frc::DifferentialDrive myRobot {right, left};
	frc::Joystick stick { 0 };
	frc::SendableChooser<std::string> chooser;
	const std::string autoNameDefault = "Default";
	const std::string autoNameCustom = "My Auto";

public:
	Robot() {
		myRobot.SetExpiration(0.1);
	}

	void RobotInit() {
		chooser.AddDefault(autoNameDefault, autoNameDefault);
		chooser.AddObject(autoNameCustom, autoNameCustom);
		frc::SmartDashboard::PutData("Auto Modes", &chooser);
	}


	void Autonomous() {
		auto autoSelected = chooser.GetSelected();
		// std::string autoSelected = frc::SmartDashboard::GetString("Auto Selector", autoNameDefault);
		std::cout << "Auto selected: " << autoSelected << std::endl;

		if (autoSelected == autoNameCustom) {
			// Custom Auto goes here
			std::cout << "Running custom Autonomous" << std::endl;
			myRobot.SetSafetyEnabled(false);
			myRobot.CurvatureDrive(0.5, 0.0, false); //go straight for 1 second
			frc::Wait(1.0);                // for 2 seconds
			myRobot.CurvatureDrive(0.5,-1, true);//turn for 0.5 seconds
			frc::Wait(0.5);
			myRobot.CurvatureDrive(0.5, 0.0, false); //go straight for 1 second
			frc::Wait(1.0);
			myRobot.CurvatureDrive(0.0, 0.0, false);  // stop robot
			frc::Wait(1.0);
		} else {
			// Default Auto goes here
			std::cout << "Running default Autonomous" << std::endl;
			myRobot.SetSafetyEnabled(false);
			myRobot.CurvatureDrive(-0.5, 0.0, false); // drive forwards half speed
			frc::Wait(2.0);                // for 2 seconds
			myRobot.CurvatureDrive(0.0, 0.0, false);  // stop robot
		}
	}


	void OperatorControl() override {
		myRobot.SetSafetyEnabled(true);
		while (IsOperatorControl() && IsEnabled()) {
			// drive with arcade style (use right stick)
			myRobot.ArcadeDrive(-stick.GetY(), stick.GetX(), false);


			if(stick.GetButton(5))
			{
				Arm.Set(.5);
			}
			else
			{
				Arm.Set(0);
			}

			if(stick.GetButton(6))
			{
				Arm.Set(-0.5);
			}
			else
			{
				Arm.Set(0):
			}





			frc::Wait(0.005);
		}
	}

	void Test() override {

	}
};

START_ROBOT_CLASS(Robot)
