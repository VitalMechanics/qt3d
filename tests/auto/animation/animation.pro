TEMPLATE = subdirs

SUBDIRS += \
    qanimationaspect \
    qanimationcliploader \
    qclipanimator \
    qblendedclipanimator \
    qchannelmapping \
    qchannelmapper \
    qclipblendvalue

qtConfig(private_tests) {
    SUBDIRS += \
        animationclip \
        fcurve \
        functionrangefinder \
        bezierevaluator \
        clipanimator \
        blendedclipanimator \
        channelmapper \
        channelmapping \
        qlerpclipblend \
        clipblendnodemanager \
        clipblendnode \
        lerpclipblend \
        clipblendnodevisitor \
        qadditiveclipblend \
        additiveclipblend \
        clipblendvalue \
        animationutils
}
