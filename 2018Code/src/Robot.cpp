#include <iostream>
#include <memory>
#include <string>


#include <XboxController.h>
#include <CameraServer.h>
#include <ADXRS450_Gyro.h>
#include <ADXL362.h>

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




	//Controllers
	frc::XboxController Xbox{1};
	frc::Joystick Stick {0};

	//Add-ons
	frc::ADXRS450_Gyro Gyro;

	//Motors
	frc::PWMTalonSRX Arm{4};
	frc::PWMTalonSRX Intake_one{5}
	frc::PWMTalonSRX Intake_two{6}

	frc::SpeedControllerGroup Intake{Intake_one, Intake_two};


	frc::PWMTalonSRX front_left {0};
	frc::PWMTalonSRX back_left {1};
	frc::PWMTalonSRX front_right {3};
	frc::PWMTalonSRX back_right {2};

	frc::SpeedControllerGroup left{front_left, back_left};
	frc::SpeedControllerGroup right{front_right, back_right};

	frc::DifferentialDrive myRobot {right, left};
	//Dashboard Choosers
	frc::SendableChooser<std::string> side;
	frc::SendableChooser<std::string> start;
	//Dashboard Options
	const std::string red = "Red";
	const std::string blue = "Blue";
	const std::string basic = "Go Forward";
	const std::string startright = "Right Start";
	const std::string startmid = "Middle Start";
	const std::string startleft = "Left Start";

public:
	Robot() {
		myRobot.SetExpiration(0.1);
	}

	void RobotInit() {
		side.AddDefault(red, red);
		side.AddObject(blue, blue);
		side.AddObject(basic, basic);
		start.AddDefault(startright, startright);
		start.AddObject(startmid, startmid);
		start.AddObject(startleft, startleft);
		frc::SmartDashboard::PutData("Color Selected", &side);
		frc::SmartDashboard::PutData("Start Position Selected", &start);
		frc::CameraServer::GetInstance()->StartAutomaticCapture();
		gyro.Reset();

	}


	void Autonomous() {

		auto Start = start.GetSelected();
		auto Color = side.GetSelected();

		std::cout << "Auto selected:Start: " << Start << "Color: " << std::endl;

		if ((Start == startleft) && (Color == blue)) {
			//make auto for left start blue

		} else if ((Start == startmid) && (Color == blue)) {
			//make auto for mid start blue

		} else if ((Start == startright) && (Color == blue)) {
			//make auto for right start blue

		} else if ((Start == startleft) && (Color == red)) {
			//make auto for left start red

		} else if ((Start == startmid) && (Color == red)) {
			//make auto for mid start red

		} else if ((Start == startright) && (Color == red)) {
			//make auto for right start red

		}else  {
			// Default Auto goes here. What do we want it to do no matter what?
			std::cout << "Running default Autonomous" << std::endl;
			myRobot.SetSafetyEnabled(false);
			myRobot.Drive(-0.25, 0.0);
			frc::Wait(8.0);
			myRobot.Drive(0.0, 0.0);
		}
	}


	void OperatorControl() override {
		myRobot.SetSafetyEnabled(true);
		while (IsOperatorControl() && IsEnabled()) {
			//myRobot.ArcadeDrive(-stick.GetY(), stick.GetX(), false); //Joy stick controls(right stick if xbox)
			myRobot.TankDrive(Xbox.GetY(), Xbox.GetX()); //Not sure this works. Test this eventually/



			if (Xbox.GetTriggerAxis(XboxController::JoystickHand(0))) //0 is left trigger
			{
				Intake.Set(-0.5);
			} else {
				Intake.Set(0);
			}
			if (Xbox.GetTriggerAxis(XboxController::JoystickHand(1)))//1 is right trigger
			{
				Intake.Set(0.5);
			} else {
				Intake.Set(0)
			}


			//Move elevator arm up(X) and down(B)
			if(Xbox.GetXButton())
			{
				Arm.Set(.5);
			}
			else
			{
				Arm.Set(0);
			}

			if(stick.GetBButton())
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
