package com.ad.sudoku.model.dao;

import com.ad.sudoku.model.SudokuBoard;
import com.ad.sudoku.model.exceptions.SudokuSQlException;
import java.util.List;
import javax.persistence.EntityManager;
import javax.persistence.Persistence;
import javax.persistence.PersistenceException;
import javax.persistence.RollbackException;

public class JpaSudokuBoardDao implements Dao<List<SudokuBoard>> {

    private String name;

    private final EntityManager entityManager =
            Persistence.createEntityManagerFactory("Sudoku")
                    .createEntityManager();

    public JpaSudokuBoardDao(String name) {
        this.name = name;
    }

    public List<SudokuBoard> readAll() {
        try {
            return entityManager
                    .createQuery("FROM SudokuBoard sb "
                            + "WHERE sb.name NOT LIKE '%_OG'", SudokuBoard.class)
                    .getResultList();
        }  catch (RollbackException e) {
            throw new SudokuSQlException("SudokuSQLException.read", e);
        } catch (PersistenceException e) {
            throw new SudokuSQlException("SudokuSQLException.read", e);
        }

    }

    @Override
    public List<SudokuBoard> read() {
        SudokuBoard board;
        SudokuBoard boardOryginal;

        try {
            board = entityManager
                    .createQuery("SELECT sb FROM SudokuBoard sb "
                            + "WHERE sb.name = :name", SudokuBoard.class)
                    .setParameter("name", name)
                    .getSingleResult();

            boardOryginal = entityManager
                    .createQuery("SELECT sb FROM SudokuBoard sb "
                            + "WHERE sb.name = :name", SudokuBoard.class)
                    .setParameter("name", name + "_OG")
                    .getSingleResult();
        } catch (RollbackException e) {
            throw new SudokuSQlException("SudokuSQLException.read", e);
        } catch (PersistenceException e) {
            throw new SudokuSQlException("SudokuSQLException.read", e);
        }



        return List.of(board, boardOryginal);
    }

    @Override
    public void write(List<SudokuBoard> obj) {
        obj.get(0).setName(name);
        obj.get(1).setName(name + "_OG");

        try {
            entityManager.getTransaction().begin();
            entityManager.persist(obj.get(0));
            entityManager.persist(obj.get(1));
            entityManager.getTransaction().commit();
        } catch (RollbackException e) {
            throw new SudokuSQlException("SudokuSQLException.write", e);
        } catch (PersistenceException e) {
            throw new SudokuSQlException("SudokuSQLException.write", e);
        }
    }

    @Override
    public void close() {
        try {
            entityManager.close();
        } catch (Exception e) {
            System.out.println("Ignoring Exception, because tried to close closed object");
        }
    }
}
