#pragma once

// Module entry points owned by this repository, declared without including the
// interpreter header so a host-neutral translation unit can build the module
// table.

void initdbg();
void initgrp();
void initgrpImage();
void initgrpText();
void initwndMgr();
