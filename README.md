# Introduction

This is the embedded software of an experimental respiration monitor belt measuring changes in thoracic or abdominal circumference during respiration. The mechanical part of the belt contains an adjustable strap connected with a linear encoder scale and a spring at the end. When the wearer breathes, the belt stretches and shrinks as the circumference changes, causing the motion of the linear encoder scale. This motion will be detected by the linear optical encoder so that we can monitor respiration.

The hardware onboard mainly includes an MSP430G2253 MCU, an AT45DB081 NOR-Flash, an HC-05 Bluetooth module, and a linear optical encoder.