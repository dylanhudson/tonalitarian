
// For monitoring MIDI messages
// From @JussiNeuralDSP on the JUCE forums
void verbose(AudioProcessor &processor, const MidiBuffer &messages)
{
    MidiBuffer::Iterator    it(messages);
    MidiMessage             msg;
    int                     samplePosition = 0;
    
    if (auto *playHead = processor.getPlayHead())
    {
        AudioPlayHead::CurrentPositionInfo info;
        
        playHead->getCurrentPosition(info);
        
        double bpm = info.bpm;
        
        while (it.getNextEvent(msg, samplePosition))
        {
            double beats = info.ppqPosition + double(samplePosition / processor.getSampleRate()) * bpm / 60.0;
            DBG("Beats: " << String::formatted("%4f", beats) << " " << msg.getDescription());
        }
    }
}
