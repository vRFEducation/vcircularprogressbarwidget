#include "VCircularProgressBar.h"
#include "ui_VCircularProgressBar.h"

#include <QGraphicsDropShadowEffect>
VCircularProgressBar::VCircularProgressBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VCircularProgressBar)
{
    ui->setupUi(this);
    reset();
}

VCircularProgressBar::~VCircularProgressBar()
{
    delete ui;
}

const QColor &VCircularProgressBar::color() const
{
    return _color;
}

void VCircularProgressBar::setColor(const QColor &newColor)
{
    if (_color == newColor)
        return;
    _color = newColor;
    updateProgress();
}

const QString &VCircularProgressBar::upperCaption() const
{
    return _upperCaption;
}

void VCircularProgressBar::setUpperCaption(const QString &newUpperCaption)
{
    if (_upperCaption == newUpperCaption)
        return;
    _upperCaption = newUpperCaption;
    ui->lblUpperCaption->setText(upperCaption());
    ui->lblUpperCaption->setVisible(upperCaption().length() != 0);

}

const QString &VCircularProgressBar::lowerCaption() const
{
    return _lowerCaption;
}

void VCircularProgressBar::setLowerCaption(const QString &newLowerCaption)
{
    if (_lowerCaption == newLowerCaption)
        return;
    _lowerCaption = newLowerCaption;
    ui->lblLowerCaption->setText(lowerCaption());
    ui->lblLowerCaption->setVisible(lowerCaption().length() != 0);

}

int VCircularProgressBar::progress() const
{
    return _progress;
}

void VCircularProgressBar::setProgress(int newProgress)
{
    if (_progress == newProgress || minimun() > newProgress || newProgress > maximum())
        return;
    _progress = newProgress;
    updateProgress();

}

int VCircularProgressBar::minimun() const
{
    return _minimun;
}

void VCircularProgressBar::setMinimun(int newMinimun)
{
    if (_minimun == newMinimun)
        return;
    _minimun = newMinimun;

}

int VCircularProgressBar::maximum() const
{
    return _maximum;
}

void VCircularProgressBar::setMaximum(int newMaximum)
{
    if (_maximum == newMaximum)
        return;
    _maximum = newMaximum;

}

bool VCircularProgressBar::isLoadingVisible() const
{
    return _isLoadingVisible;
}

void VCircularProgressBar::setIsLoadingVisible(bool newIsLoadingVisible)
{
    if (_isLoadingVisible == newIsLoadingVisible)
        return;
    _isLoadingVisible = newIsLoadingVisible;
    ui->lblLoading->setVisible(isLoadingVisible());

}

bool VCircularProgressBar::isShadowEnabled() const
{
    return _isShadowEnabled;
}

void VCircularProgressBar::setIsShadowEnabled(bool newIsShadowEnabled)
{
    if (_isShadowEnabled == newIsShadowEnabled)
        return;
    _isShadowEnabled = newIsShadowEnabled;
    setShadow();

}

void VCircularProgressBar::resizeEvent(QResizeEvent *ev)
{
    if (ev->size().height() != ev->size().width()) {
        int min = std::min(ev->size().height(), ev->size().width());
        this->resize(min, min);
        auto margin = (ui->frmContainer->width() - ui->frmContent->width() )/2;
        ui->frmContainer->layout()->setContentsMargins(margin,margin,margin,margin);
    }
    updateFramesSize();

}

void VCircularProgressBar::showEvent(QShowEvent *ev)
{
    updateFramesSize();
}

const QFont &VCircularProgressBar::font() const
{
    return _font;
}

void VCircularProgressBar::setFont(const QFont &newFont)
{
    if (_font == newFont)
        return;
    _font = newFont;
    ui->lblPercentage->setFont(font());
    QFont tmpFont(font());
    tmpFont.setPointSize(tmpFont.pointSize() * 0.6);

    ui->lblUpperCaption->setFont(tmpFont);
    ui->lblLowerCaption->setFont(tmpFont);
    ui->lblLoading->setFont(tmpFont);

}

void VCircularProgressBar::setShadow()
{
    QGraphicsDropShadowEffect *shadow = nullptr;
    if (isShadowEnabled()) {
        shadow = new QGraphicsDropShadowEffect(this);
        shadow->setBlurRadius(20);
        shadow->setXOffset(0);
        shadow->setYOffset(0);
        shadow->setColor(QColor(0,0,0,120));
    }

    ui->frmBackground->setGraphicsEffect(shadow);
}

void VCircularProgressBar::updateProgress(){
    auto value = (maximum() - progress()) / (maximum() * 1.0);
    QString stylesheet = QString("border-radius: %4px;\nbackground-color: qconicalgradient(cx:0.5, cy:0.5, angle:90, stop:%1 rgba(255, 0, 127, 0), stop:%2 %3);")
            .arg(value - 0.001)
            .arg(value)
            .arg(color().name())
            .arg(ui->frmProgressBar->width() / 2);
    ui->frmProgressBar->setStyleSheet(stylesheet);
    style()->polish(ui->frmProgressBar);

    auto valueText = QString("<span style='font-size:48pt;'>%1</span><span style='font-size:36pt; vertical-align:super;'>%</span>").arg(progress());
    ui->lblPercentage->setText(valueText);


}

void VCircularProgressBar::reset()
{
    setMinimun(0);
    setMaximum(100);
    setProgress(25);
    setIsLoadingVisible(true);
    setIsShadowEnabled(true);
    setColor(QColor(0, 255, 127, 255));
    setUpperCaption("<span style=\" color:#5555ff;\">Your</span> Application Name");
    setLowerCaption("By: vrfEducation");
}

void VCircularProgressBar::updateFramesSize()
{
    QList<QWidget *> widgetList;
    widgetList << ui->frmBackground << ui->frmProgressBar << ui->frmContainer;
    foreach (auto w, widgetList) {
        bool styleUpdated = false;
        QStringList styles = w->styleSheet().split("\n");
        for (int i = 0; i < styles.length(); ++i) {
            if (styles[i].contains("border-radius")) {
                styles[i] = QString("border-radius:%1px;").arg(w->height() / 2);
                styleUpdated = true;
                break;
            }
        }
        if (styleUpdated) {
            w->setStyleSheet(styles.join("\n"));
            style()->polish(w);
        }
    }

}
