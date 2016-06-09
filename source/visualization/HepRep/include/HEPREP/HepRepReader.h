// -*- C++ -*-
// AID-GENERATED
// =========================================================================
// This class was generated by AID - Abstract Interface Definition          
// DO NOT MODIFY, but use the org.freehep.aid.Aid utility to regenerate it. 
// =========================================================================
#ifndef HEPREP_HEPREPREADER_H
#define HEPREP_HEPREPREADER_H 1

// Copyright 2002-2003, Freehep.

#include <string>

namespace HEPREP {

class HepRep;

/**
 * HepRepReader interface.
 *
 * @author Mark Donszelmann
 */
class HepRepReader {

public: 
    /// Destructor.
    virtual ~HepRepReader() { /* nop */; }

    /**
     * Closes the reader and its underlying stream.
     *
     * @return false in case of a stream problem.
     */
    virtual bool close() = 0;

    /**
     * Allows random access.
     *
     * @return true if this reader provides random access
     */
    virtual bool hasRandomAccess() = 0;

    /**
     * Reads a HepRep by name (random access only).
     *
     * @param name for the heprep to be read.
     * @return heprep.
     */
    virtual HepRep * read(std::string name) = 0;

    /**
     * Allows for sequential access.
     *
     * @return true if sequential access is possible.
     */
    virtual bool hasSequentialAccess() = 0;

    /**
     * Resets a sequential HepRep reader.
     *
     * @return false in case of a stream problem.
     */
    virtual bool reset() = 0;

    /**
     * Is there a next heprep.
     *
     * @return true if the next heprep is available.
     */
    virtual bool hasNext() = 0;

    /**
     * Reads the next HepRep from the Reader.
     *
     * @return heprep.
     */
    virtual HepRep * next() = 0;
}; // class
} // namespace HEPREP
#endif /* ifndef HEPREP_HEPREPREADER_H */