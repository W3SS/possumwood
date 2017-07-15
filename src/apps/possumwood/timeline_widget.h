#pragma once

#include "timeline.h"

/// A simple stand-alone widget, allowing to change the current time and star/end of the timelne.
/// Directly changes the current time in App singleton, which in turn fires off a signal
/// to all registered listeners.
class TimelineWidget : public QWidget {
	public:
		TimelineWidget(QWidget* parent = NULL);

	protected:
	private:
		Timeline* m_timeline;
};